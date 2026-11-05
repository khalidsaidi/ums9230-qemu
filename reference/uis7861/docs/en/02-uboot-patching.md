# 02. Analyzing and Patching the u-boot Binary

## The Boot-Time Wall: Raw Binary Edits Get Rejected

Even after gaining write access to `uboot_a`/`uboot_b` using the method in
[01](01-download-mode-to-fastbootd.md), simply writing back a file that was
**directly byte-edited** from a pristine `uboot_a.bin` results in the device
failing to boot at all -- no display output, no backlight -- regardless of
what was changed (even a single byte in an unused, never-executed region).
The stock image always boots fine. This isn't a write failure (a readback
confirmed the write itself succeeded correctly), so there must be a **boot-time
integrity check**, somewhere in the stage *before* u-boot itself runs
(SPL/FDL1), that compares the written `uboot_a`/`uboot_b` content against
some reference (checksum/hash) and refuses to execute it on mismatch. This
check logic lives in SPL/FDL1, which is read-protected from Download mode
(`spl_a.bin`/`spl_b.bin` always read back as all zero), so it can't be
analyzed directly.

## Workaround: the Patch-Post-Verification Technique

Using `magic64.exe`/`difftool.exe` from
[TomKing062/unisoc_chipram_signcheck_exploit](https://github.com/TomKing062/unisoc_chipram_signcheck_exploit).

**How it works**: the original payload bytes are left completely untouched;
a small "jump stub" is appended right before the payload. At boot time, this
jump stub runs first, writes a **patch table** (address + new-value pairs)
embedded at the end of the file into memory, and only then jumps to the
original payload. In other words, **the static file content (what gets
checked) stays unmodified**, while **the patch is applied by
self-modification at runtime** -- so the boot-time integrity check passes.

### Procedure

1. Copy the pristine (unmodified) `uboot_a.bin`, and produce a version with
   the desired patches written directly as raw bytes
   (`uboot_a_patched_src_XXX.bin`)
2. Use `difftool` to produce an image containing the runtime patch table:
   ```bash
   ./difftool.exe uboot_a_patched_src_XXX.bin patched.bin 0x9F000000 uboot_final_XXX.bin
   ```
   (`patched.bin` is a fixed framework generated once from the unmodified
   image via `magic64.exe`)
3. The output file can slightly exceed the partition capacity
   (`0x300000` bytes), so **truncate it to the first `0x300000` bytes**
   before writing (the actual content -- header, payload, and patch table --
   fits well within that range, so truncating the tail is safe)
4. Write it with `Flash-Raw.ps1 -Unsigned` (see [03](03-unsigned-flashing.md))

**Every u-boot patch from here on must be built this way. Never write back a
raw, directly-edited file.**

## The Verification Logic Inside u-boot (Ghidra Analysis)

### Two Layers: a Unisoc-Proprietary Layer, and Standard AVB

This device has **two layers of verification**: a **Unisoc-proprietary layer
(`root_of_trust` / `sprd_verify_cert`)**, and **standard Google AVB
(`avb_slot_verify`)**. libavb source strings are embedded in the u-boot
binary, confirming the standard AVB implementation is genuinely present. The
Unisoc layer runs **before** AVB, and the standard AVB verification result is
never reached unless you get past the Unisoc layer first.

- The gate function for the Unisoc layer: `set_root_of_trust`
- The entry point for standard AVB: `avb_slot_verify` (identified via the
  single xref to the string `"Rebooting because of dm-verity corruption"`)

Call chain (inside the normal-boot handler):
```
FUN_XXXX()   Converts the AVB verification result into cmdline properties such as androidboot.vbmeta.pubkey=...
FUN_XXXX()   Logs "SKIP VERIFY" etc. depending on verifiedbootstate
FUN_XXXX()   <- The body of the Unisoc-proprietary root_of_trust check (set_root_of_trust)
```

### Patch 1: root_of_trust Bypass

Inside the caller function, change the `CBZ` instruction that checks the
return value of `set_root_of_trust(...)` into an unconditional branch `B`, so
it always takes the "success" path regardless of the actual return value.

```
Original: CBZ W0, #<target>   ; 0x340000xx
Patched:  B #<target>          ; 0x14000xxx
```

Turning a CBZ/CBNZ/TBZ/TBNZ into a B (unconditional branch) just means
recomputing imm26 and encoding `0x14000000 | imm26` -- about the simplest
kind of patch there is.

### Two Real Root Causes Inside AVB Verification

The root_of_trust bypass alone wasn't enough in some cases. A function called
from inside `set_root_of_trust` contains a **deliberate infinite loop acting
as a safety device**, triggered whenever the AVB verification result is
non-zero:

```c
undefined8 FUN_XXXX(undefined4 param_1, undefined4 param_2)
{
  int *piVar1 = (int *)FUN_YYYY(0x36, param_1, param_2);
  if (*piVar1 != 0) {
    /* logging */
    do { /* deliberate infinite loop */ } while (true);
  }
  return 0;
}
```

With a disabled vbmeta, this check's result comes back non-zero, and the
device enters this infinite loop. This explains why the root_of_trust bypass
alone had no effect: this function itself never returns, so execution never
even reaches the code that checks its return value.

Digging further, the root cause behind this loop being entered turned out to
be **an actual implementation bug inside `avb_slot_verify` itself**. In the
dedicated branch of `load_and_verify_vbmeta` that handles a vbmeta with the
`VERIFICATION_DISABLED` bit set (a simplified path for already-disabled
vbmeta), an ops function pointer used to query a partition's size is called
**without a null check**:

```c
iVar6 = (**(code **)(ops + 0x58))(ops, partition_name, &out_size);  // <- no null check
```

Every *other* ops function pointer (at offsets `+0x18, 0x30, 0x38, 0x50,
0x60, 0x68`) is null-checked beforehand with an `assert_fail: ops->xxx`
pattern -- only `+0x58` (presumably `get_size_of_partition`) is missing that
check. On this device's AVB ops implementation, `+0x58` is left unimplemented
(an invalid value), so calling it directly crashes immediately. This is a
gap in the vendor's own implementation, and is the direct cause of the
non-zero result mentioned above.

### How It Was Found: Bisection via Print Markers

Planting an infinite loop and bisecting on "does it hang, or does it shut
down" stops working once you've fixed one crash -- **every subsequent test
starts looking like a "hang"** and becomes indistinguishable (past a certain
point on screen, nothing new gets drawn at all).

The fix was to switch to a code-cave patch that **doesn't loop**: it prints a
custom message on screen when execution reaches that point, then continues
on with the original processing as normal (saving/restoring x0/x1 around the
call, actually calling the target function, and continuing execution). This
lets you confirm "did we reach this point" without ever halting execution.
This technique is what pinned down the exact location of the infinite loop
described above.

**Caveat**: when redirecting an existing function call through a code cave
like this, you must save and restore **all AAPCS64 caller-saved (temporary)
registers X0-X17**. Be especially careful when inserting a checkpoint right
before a tail call. Just before a tail call, the caller has usually already
set up the arguments (X0-X3, etc.) for the next function; if a diagnostic
print function called from inside the checkpoint clobbers those registers,
execution ends up jumping to the kernel (or whatever the tail call target is)
with the wrong arguments, causing a mysterious crash or hang (this project
actually shipped exactly this kind of broken patch once).

## Final Patch Set (Verified Working)

| # | What it does | Type |
|---|---|---|
| 1 | root_of_trust bypass (CBZ -> B) | Simple overwrite |
| 2 | Skip the unchecked ops function pointer call inside avb_slot_verify | Code cave. At the redirected target, runs `*param_3(size output) = 0; return 0;` before resuming |
| 3 | Bypass the deliberate infinite loop in the function reached from `set_root_of_trust` (CBZ -> B) | Simple overwrite |

With a disabled vbmeta (top-level + all child vbmetas, flags = `0x3` =
`VERIFICATION_DISABLED | HASHTREE_DISABLED`) and these three patches applied,
a normal boot (power-on) produces:

```
enter boot mode 2                          <- normal boot mode, as expected
set_root_of_trust succeeded.
enter mode normal, consume time: 4568ms    <- completed, no loop
```

...after which it jumps cleanly into the kernel and reaches the Android
initialization phase.

## Behavior When Modifying vbmeta

| What was modified | Symptom | Cause |
|---|---|---|
| Top-level vbmeta modified on its own | u-boot stops booting | The Unisoc-proprietary layer (root_of_trust) detects the top-level vbmeta's state and its safety device kicks in. Resolved by the patches above |
| Only a child vbmeta (system/vendor/product/system_ext) modified, top-level left stock | u-boot gets through, but a delayed kernel panic follows (`Attempted to kill the init task!`) | The top-level vbmeta's AVB chain descriptors (hashes of the child vbmetas) are stale/stock, so the kernel detects the mismatch and panics |

**Conclusion**: the top-level vbmeta and the child vbmetas (system, vendor,
product, system_ext) must always be disabled together.

### AVB Image Format (for editing the flags directly)

- A fixed 256-byte header, magic `"AVB0"` (first 4 bytes)
- The flags field is at header offset 120, 4 bytes, **big-endian**
  - `0x1` = `AVB_VBMETA_IMAGE_FLAGS_HASHTREE_DISABLED`
  - `0x2` = `AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED`
  - `0x3` = both disabled
- `fastboot --disable-verity --disable-verification` can fail with
  `rewrite_vbmeta_buffer()` unable to find the footer, due to padding in a
  dumped image -- directly patching the flags byte as above is more reliable.
