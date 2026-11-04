# ums9230-qemu

A minimal QEMU machine (`-machine ums9230`) that emulates just enough of the
Unisoc **UMS9230 / T606** SoC to boot the SPRD **trustos** (Trusty TEE) firmware
and run its vbmeta verification, demonstrating the **`-11` (rejected) vs `0`
(accepted)** result.

## What it does

- Boots the trustos payload (a raw slice of `trustos_a.img`) from RAM at
  `0x80000000`.
- Provides a UART (PL011 @ `0x200b0000`), GICv3, a timer, and a **crypto-engine
  MMIO** device (`0x54000000`) that performs real SHA-256 + RSA-4096.
- Drives `avb_vbmeta_image_verify` (`0x6ed70`) against `vbmeta-stock.img` and
  returns the AVB result:
  - **`3`** (`AVB_VBMETA_IMAGE_RESULT_UNSUPPORTED_VERSION`) → maps to trusty
    **`-11`** on the unpatched image.
  - **`0`** on the patched image (the trustos patch at file offset `0x4ae44`:
    `00 00 80 52 C0 03 5F D6` = `mov w0,#0; ret`).

## Layout

```
ums9230.c                     the QEMU machine (drop into qemu/hw/arm/)
firmware/trustos_a.img        trustos image (proprietary, extracted from device)
firmware/vbmeta-stock.img     vbmeta used by the verify test
scripts/
  build.sh                    clone QEMU + integrate + build qemu-system-aarch64
  regen_payload.sh            trustos_a.img[0x200:] -> build/trustos-payload.bin
  run.sh                      run the emulator against the payload
  patches/                    payload patches that make the verifier run
```

## Build

Requires Linux (tested in WSL2), git, a C toolchain, ninja, meson, python3.

```sh
./scripts/build.sh
```

This clones QEMU into `./qemu`, copies `ums9230.c` into `hw/arm/`, patches the ARM CPU for Secure-EL1 reset, then registers it
in `hw/arm/meson.build` + `hw/arm/Kconfig`, configures an aarch64-only build,
and compiles `qemu/build/qemu-system-aarch64`.

## Run

```sh
./scripts/regen_payload.sh        # produce build/trustos-payload.bin
python3 scripts/patches/patch_skip_malloc.py
python3 scripts/patches/patch_free.py
python3 scripts/patches/patch_print.py
python3 scripts/patches/patch_idle.py
./scripts/run.sh
```

The verifier's return value is captured into the scratch `hash` slot and printed
as `hash=0x3` (`-11`) for the stock image.

## Result

- **unpatched** → `hash=0x3` (`-11`, rejected)
- **patched** (`trustos_a.img` @ `0x4ae44` → `mov w0,#0; ret`) → `0`

## Limitations (honest)

- The crypto engine does real SHA-256 + RSA-4096 (math verified against test
  vectors); its register map is a documented approximation of the Unisoc CE.
- `-11` is demonstrated through the **version check** path, not the full
  RSA/SHA compare (async worker → `avb_slot_verify`).
- Only the trustos firmware boots; Android/Linux userspace is not emulated.
- This is a verification/development tool, not a full device emulator, and not
  a substitute for flashing the patched image onto physical hardware.

## Firmware

`firmware/trustos_a.img` and `firmware/vbmeta-stock.img` are proprietary images
extracted from a Blackview Tab 15 Pro. They are included so the emulator runs
out of the box; you are responsible for any redistribution obligations.
