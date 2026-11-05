# UIS7861/UIS7863 (Unisoc UMS9230 / QOGIRL6) u-boot AVB Bypass

[日本語](README.ja.md)

A write-up and toolkit for bypassing both the Unisoc-proprietary secure boot
layer (`root_of_trust`) and standard Google AVB (`avb_slot_verify`) inside
u-boot on an Android car head unit (Unisoc UMS9230 family, QOGIRL6 platform),
so that arbitrary modified images (e.g. a GSI) can be booted.

## Target Device

- SoC: Unisoc/Spreadtrum UMS9230 (QOGIRL6), UIS7861/UIS7863
- `ro.hardware`: `uis7861_6h10`
- Assumes the bootloader has already been unlocked via
  [CVE-2022-38694](https://nvd.nist.gov/vuln/detail/CVE-2022-38694) (a
  vulnerability that bypasses BROM Download mode's signature verification via
  `exec_addr`/`loadexec`).

## Disclaimer

- This repository documents **legitimate modification/security research on a
  device the author owns**.
- The procedures described disable this device's root_of_trust/AVB
  verification. **Doing so voids any warranty and risks bricking the
  device.** Proceed entirely at your own risk.
- Because Download mode (BROM) runs from mask ROM, there is generally a
  recovery path no matter how badly u-boot and everything after it gets
  broken -- but this is not a 100% guarantee.

## Overview: Two Independent Walls

Getting a modified image written and actually executed involved clearing two
independent walls.

1. **The write-time wall** (FDL2 signature verification) -- a signed FDL2
   verifies the signature of the write_part data itself, and refuses to
   write a modified image.
   -> [`docs/en/01-download-mode-to-fastbootd.md`](docs/en/01-download-mode-to-fastbootd.md) /
   [`docs/en/03-unsigned-flashing.md`](docs/en/03-unsigned-flashing.md)
2. **The boot-time wall** (u-boot's own integrity check, plus
   root_of_trust/AVB) -- even once you can write past the signature check, a
   directly byte-edited u-boot payload gets rejected by a boot-time integrity
   check. Getting past that still leaves both the Unisoc-proprietary
   root_of_trust layer and standard AVB to deal with.
   -> [`docs/en/02-uboot-patching.md`](docs/en/02-uboot-patching.md)

## Documentation

| Document | Contents |
|---|---|
| [01. Exploiting Download Mode to Reach fastbootd](docs/en/01-download-mode-to-fastbootd.md) | BROM signature-verification bypass via CVE-2022-38694, Download mode operations, getting into fastbootd |
| [02. Analyzing and Patching the u-boot Binary](docs/en/02-uboot-patching.md) | The Ghidra analysis process, the root_of_trust/AVB bypass patches, the Patch-Post-Verification technique |
| [03. Flashing Images by Exploiting the Vulnerability](docs/en/03-unsigned-flashing.md) | The `-Unsigned` write path via an unsigned FDL, the GSI install procedure |

Japanese versions are available under [`docs/ja/`](docs/ja/).

## scripts/

PowerShell scripts that automate the procedures in this write-up. See each
doc above for detailed usage.

- `Flash-Raw.ps1` -- write to an arbitrary partition from Download mode.
  `-Unsigned` enables the signature-bypass write path.
- `Enter-Fastbootd.ps1` -- gets into fastbootd via the `misc` partition (BCB).
- `Dump-Boot.ps1` -- read-only dump of `spl_a`/`spl_b`/`uboot_a`/`uboot_b`.
- `Dump-Logs.ps1` -- read-only dump of the `uboot_log`/`sysdumpdb` partitions
  (used to recover u-boot console logs / kernel crash dumps).
- `ConvertTo-SparseImage.ps1` -- converts a raw img to the Android sparse
  format (works around a fastboot raw-splitting bug).

These scripts depend on the following third-party tools, which are **not**
bundled in this repository for licensing reasons. Obtain them from their
respective sources:

- `spd_dump` (libusb build) -- [TomKing062/spreadtrum_flash](https://github.com/TomKing062/spreadtrum_flash)
- `magic64.exe` / `difftool.exe` (the Patch-Post-Verification technique) --
  [TomKing062/unisoc_chipram_signcheck_exploit](https://github.com/TomKing062/unisoc_chipram_signcheck_exploit)
- The unsigned FDL / `custom_exec_no_verify_*.bin` --
  [TomKing062/CVE-2022-38694_unlock_bootloader](https://github.com/TomKing062/CVE-2022-38694_unlock_bootloader)

## .claude/

This repository also includes the [Claude Code](https://claude.com/product/claude-code)
skill/agent definitions actually used while doing this research, under
[`.claude/`](.claude/README.md), for anyone who wants to reproduce the same
workflow.

## Credits

- [TomKing062](https://github.com/TomKing062) -- the CVE-2022-38694 PoC
  implementation, `spreadtrum_flash`, and `unisoc_chipram_signcheck_exploit`.
  This whole project builds on that work.
- Whoever discovered/reported CVE-2022-38694 itself (the Unisoc BROM Download
  mode signature-verification bypass).

## License

The original scripts and documentation in this repository are released under
the [MIT License](LICENSE). The third-party tools listed above are governed
by their own respective source repositories' licenses.
