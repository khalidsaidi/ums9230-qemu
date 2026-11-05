# 01. Exploiting Download Mode to Reach fastbootd

## About Download Mode (BROM)

Unisoc/Spreadtrum SoCs enter BROM (Boot ROM, a mask ROM)'s **Download mode**
at power-on under certain conditions (a button combination, or a failure to
boot normally). Since BROM is burned into the chip, Download mode itself
generally keeps working no matter how badly u-boot and everything after it
gets broken. This is the "last resort" recovery path this project relies on.

To use Download mode, you connect from a PC over USB with a tool like
`spd_dump`, which loads two loader stages in sequence -- FDL1, then FDL2.
Only once both are loaded can you read/write partitions, etc.

```
PC --USB--> BROM (Download mode) --FDL1--> FDL1 --FDL2--> FDL2 (read_part/write_part etc. now available)
```

## CVE-2022-38694: Bypassing BROM's Signature Verification

A stock BROM verifies the signature of any FDL1/FDL2 it loads. Trying to load
an unsigned (modified) FDL1/FDL2 gets rejected.

[CVE-2022-38694](https://nvd.nist.gov/vuln/detail/CVE-2022-38694) is a
vulnerability that lets you bypass this signature check **every session**
using BROM's `exec_addr` command (jump-and-execute at an arbitrary address).
[TomKing062/CVE-2022-38694_unlock_bootloader](https://github.com/TomKing062/CVE-2022-38694_unlock_bootloader)
has a working PoC implementation: it executes a small shellcode
(`custom_exec_no_verify_65015f08.bin`) via `exec_addr`, which disables
signature verification for any FDL1/FDL2 loaded afterward.

The actual command sequence (from `unlock_autopatch_9230.bat`):

```
spd_dump exec_addr 0x65015f08 fdl fdl1-dl.bin 0x65000800 fdl fdl2-dl.bin 0x9efffe00 exec ...
```

- `exec_addr 0x65015f08` -- jumps to a specific address inside BROM and runs
  the shellcode (`custom_exec_no_verify_65015f08.bin`) that patches out
  signature verification
- `fdl fdl1-dl.bin 0x65000800` -- with verification now disabled, loads the
  **unsigned** FDL1 at that address
- `fdl fdl2-dl.bin 0x9efffe00` -- likewise loads the unsigned FDL2

This is not a one-time patch; it has to be **re-applied every time you
connect to BROM** (BROM's own code is untouched -- the patch is a runtime
patch in RAM, so it's gone once power is cut).

## Tools Used

- `spd_dump` (libusb build) -- separate from the commonly-distributed build
  that assumes SPRD's stock driver, you need the build from
  `TomKing062/spreadtrum_flash`'s `stable_*` releases, which works with
  libusb + a Zadig/WinUSB driver. The stock-driver build (which goes through
  `Channel9.dll`) could not connect in a WinUSB driver environment.
- The unsigned FDL set (`fdl1-dl.bin`, `fdl2-dl.bin`,
  `custom_exec_no_verify_65015f08.bin`) -- from the
  `CVE-2022-38694_unlock_bootloader` repository.

## Getting Into fastbootd

You reach fastbootd (fastboot in userspace, used to operate on dynamic
partitions) the standard Android way, via the BCB (Boot Control Block, stored
in the `misc` partition). `misc` is not a signature-protected partition, so
`spd_dump` can write to it directly.

`scripts/Enter-Fastbootd.ps1` gets you into fastbootd by writing the
appropriate BCB command (equivalent to `boot-fastboot`) into the `misc`
partition, then rebooting.

```powershell
.\Enter-Fastbootd.ps1
```

Once in fastbootd, ordinary `fastboot` commands (`fastboot devices`,
`fastboot flash`, `fastboot delete-logical-partition`, etc.) work as usual.

## Download Mode as a Recovery Path

Even if modifying u-boot leaves the device completely unable to boot (a
blank screen), forcing the device into Download mode via the power button
etc. can usually recover it (this project ran into exactly that situation
several times while experimenting with u-boot modifications, and every time
Download mode got it back). **Before starting any modification work, strongly
consider backing up the stock `uboot_a`/`uboot_b`/`super`/etc. via Download
mode first** (`Dump-Boot.ps1`, and dumping the whole `super` via
`Flash-Raw.ps1`).
