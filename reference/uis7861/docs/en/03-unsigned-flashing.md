# 03. Flashing Images by Exploiting the Vulnerability

## Symptom: a Signed FDL2 Refuses to Write a Modified Image

Using the stock, signed `fdl1-sign.bin`/`fdl2-sign.bin` to `write_part` a
**modified** image to `uboot_a`/`uboot_b` fails: no ACK comes back for the
final chunk, and it errors out with something like `unexpected response`,
leaving the write incomplete (short of the target size). A stock
(unmodified) image always writes through cleanly.

## Cause: Signature Verification at the FDL2 Level

`spd_dump`'s (spreadtrum_flash) source, in `common.c`'s `load_partition()`
function, contains something like:

```c
if (!ret) {
    if (n == n64) ERR_EXIT("signature verification of \"%s\" failed or timeout reached\n", name);
    else ERR_EXIT("timeout reached\n");
}
```

When no ACK arrives for the final chunk, the tool's own author explicitly
labels it as a signature verification failure. In other words, **a signed
FDL2 verifies the signature of the write_part data itself**, and (partially)
rejects writing a modified `uboot_a`/`uboot_b`. This is a completely separate
protection from u-boot's own runtime verification (root_of_trust, AVB -- see
[02](02-uboot-patching.md)); it's **write-time protection at the FDL2
level**.

## Solution: Writing via an Unsigned FDL

This reuses the CVE-2022-38694 `exec_addr` bypass described in
[01](01-download-mode-to-fastbootd.md), this time applied when loading FDL2
as well. That lets you load the **unsigned `fdl1-dl.bin`/`fdl2-dl.bin`**,
which perform no signature verification at all, sidestepping the write-time
data-signature check entirely (verified by comparing a readback byte-for-byte
against the source).

```
spd_dump exec_addr 0x65015f08 fdl fdl1-dl.bin 0x65000800 fdl fdl2-dl.bin 0x9efffe00 exec write_part <partition> <offset> <size> <file> reset
```

## `Flash-Raw.ps1 -Unsigned`

`scripts/Flash-Raw.ps1` implements this as the `-Unsigned` switch.

```powershell
# Write a modified image to uboot_a/uboot_b (signature bypass required)
.\Flash-Raw.ps1 -Unsigned -Files @(
    "uboot_a=.\uboot_a_patched.bin",
    "uboot_b=.\uboot_b_patched.bin"
)
```

- Without `-Unsigned`, it writes through the stock, signed
  `fdl1-sign.bin`/`fdl2-sign.bin` as normal. Unprotected partitions such as
  `vbmeta_*`/`misc` don't need `-Unsigned`, but it does no harm if used.
- `-Unsigned` is required for writing a modified image to a protected
  partition like `uboot_a`/`uboot_b`.
- This needs the libusb build, `spd_dump_dl.exe` (from
  `TomKing062/spreadtrum_flash`'s `stable_*` releases), rather than the
  regular `spd_dump.exe`.

## Applying This: Installing a GSI

The same mechanism can be used to swap `system_a` for a Generic System Image
(GSI). The general idea is as follows.

### Freeing Up Space in the `super` Partition

Android Virtual A/B reserves `*-cow` regions inside the `super` partition for
OTA-update snapshots. On a stock device, this leaves almost no unallocated
space in `super`, which isn't enough to `create-logical-partition` for a
GSI's `system.img` (usually larger than the stock one). Shrinking unused
`*-cow` reservations to zero frees up room:

```powershell
fastboot resize-logical-partition system_a-cow 0
fastboot resize-logical-partition vendor_a-cow 0
fastboot resize-logical-partition product_a-cow 0
# etc.
```

Since this rewrites the contents of `super`, strongly consider backing up the
whole `super.img` first (readable/writable in full via `Flash-Raw.ps1`).

`product_a`/`system_ext_a`/`vendor_a` are marked as `required` mounts in the
fstab; deleting them has been confirmed on real hardware to leave the device
unable to boot. Limit the GSI swap to `system_a` only.

### Disabling Child vbmeta + Swapping system_a

1. Rewrite the flags of every child vbmeta (system/vendor/product/system_ext/
   odm) **except the top-level one** to `0x00000003`, then `fastboot flash`
   each (see the AVB image format in [02](02-uboot-patching.md))
2. Delete `system_a` with `delete-logical-partition`, then
   `create-logical-partition` at exactly the GSI `system.img`'s size, and
   `flash` it
3. `fastboot -w` to reinitialize `userdata`
4. `reboot`

### Working Around fastboot's Raw-Sparse Auto-Split Bug

When sending a raw file larger than `max-download-size`, some fastboot
versions try to auto-split it into sparse chunks, and fail with "Invalid
sparse file format at header magic" / "Error reading sparse file". The
workaround is to pre-convert to a proper sparse image with
`ConvertTo-SparseImage.ps1` (a minimal implementation that performs no
compression, and just wraps the whole file as a single raw chunk in sparse
format) before sending it.
