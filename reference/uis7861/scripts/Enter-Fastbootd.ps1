<#
.SYNOPSIS
    Get a Unisoc/Spreadtrum device from Download mode (BROM+FDL) straight into
    fastbootd (the userspace fastboot that can operate on dynamic partitions /
    super.img) without booting Android first.

.DESCRIPTION
    How it works:
    Android's "adb reboot fastboot" simply writes the string "boot-fastboot"
    into the 32-byte command field at the start of the BCB (Bootloader Control
    Block) stored in the misc partition, then reboots. The bootloader sees this,
    boots recovery, and recovery switches over to fastbootd.
    (Spec: https://source.android.com/docs/core/architecture/bootloader/fastbootd)

    This script uses spd_dump (https://github.com/ilyakurdyukov/spreadtrum_flash)
    to rewrite just the command field of the misc partition while still in
    Download mode, then resets. By default it writes the plain AOSP
    "boot-fastboot" command string into the field. If your device's recovery
    doesn't react to that (some vendor recoveries expect a different exact
    byte layout), pass -CapturedBcb with a real BCB blob captured from a
    working "adb reboot fastboot" on your own device (e.g. via USB traffic
    capture) instead.

.NOTES
    Prerequisites:
    - Extract spd_dump64.zip (Releases:
      https://github.com/ilyakurdyukov/spreadtrum_flash/releases) to obtain
      spd_dump.exe.
    - Using Zadig (https://zadig.akeo.ie/), assign the libusb-win32 / WinUSB
      driver to the interface enumerated in Download mode (e.g. "SPRD U2S
      Diagnostics").
    - Note down the FDL1/FDL2 files and their load addresses used to flash
      this device in Download mode (found in the PAC's XML, or in a GUI
      flashing tool's log).
    - The misc partition name can differ by device. The first time, dump the
      partition list with
      `.\spd_dump.exe fdl <fdl1> <addr1> fdl <fdl2> <addr2> partition_list partition.xml`
      and confirm "misc" exists before using this script.

.EXAMPLE
    # Enter fastbootd using the plain "boot-fastboot" BCB command string
    .\Enter-Fastbootd.ps1

.EXAMPLE
    # Use a real BCB blob you captured from your own device, and a different FDL
    .\Enter-Fastbootd.ps1 -Fdl1 .\fdl1-sign.bin -Fdl1Addr 0x5500 -Fdl2 .\fdl2-sign.bin -Fdl2Addr 0x9efffe00 -CapturedBcb .\bcb-fastboot.bin
#>

param(
    [string]$SpdDump  = ".\spd_dump.exe",
    # Defaults match this project's uis7861_6h10 device; override for other devices.
    [string]$Fdl1     = ".\fdl1-sign.bin",
    [string]$Fdl1Addr = "0x65000800",
    [string]$Fdl2     = ".\fdl2-sign.bin",
    [string]$Fdl2Addr = "0x9EFFFE00",
    [string]$MiscPart = "misc",
    [int]   $BcbSize  = 0x800,      # Only the first 2048 bytes of the BCB (bootloader_message) struct matter
    [string]$BcbCommand = "boot-fastboot",
    # Path to a real BCB blob captured from your own device (optional). If not
    # supplied or not found, falls back to writing $BcbCommand into the
    # command field of the currently-read misc partition.
    [string]$CapturedBcb = "",
    [switch]$Restore                # If set, writes back misc_backup.bin as-is to return to normal boot
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $SpdDump))  { throw "spd_dump.exe not found: $SpdDump" }
if (-not (Test-Path $Fdl1))     { throw "FDL1 not found: $Fdl1" }
if (-not (Test-Path $Fdl2))     { throw "FDL2 not found: $Fdl2" }

$work    = Join-Path $PSScriptRoot "work"
New-Item -ItemType Directory -Force -Path $work | Out-Null
$backup  = Join-Path $work "misc_backup.bin"
$patched = Join-Path $work "misc_patched.bin"

function Invoke-SpdDump {
    param([string[]]$SpdArgs)
    Write-Host ">> $SpdDump $($SpdArgs -join ' ')" -ForegroundColor DarkGray
    & $SpdDump @SpdArgs
    if ($LASTEXITCODE -ne 0) {
        throw "spd_dump exited with an error (exit $LASTEXITCODE). Check that the device is waiting in Download mode, and that the FDL paths/addresses are correct."
    }
}

if ($Restore) {
    if (-not (Test-Path $backup)) { throw "Backup not found: $backup (you need to have run this script normally first, which saves off the original misc content)" }
    Write-Host "[1/1] Writing back the original misc content to return to normal boot..." -ForegroundColor Cyan
    Invoke-SpdDump @("fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr, "write_part", $MiscPart, $backup, "reset")
    Write-Host "Done. The device should boot normally." -ForegroundColor Green
    return
}

Write-Host "[1/4] Connecting to Download mode and reading the current misc (BCB)..." -ForegroundColor Cyan
Invoke-SpdDump @("fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr, "read_part", $MiscPart, "0", $BcbSize, $backup)
if (-not (Test-Path $backup)) { throw "Failed to read misc." }

if ($CapturedBcb -and (Test-Path $CapturedBcb)) {
    Write-Host "[2/4] Using the captured real BCB ($CapturedBcb)..." -ForegroundColor Cyan
    Copy-Item -Path $CapturedBcb -Destination $patched -Force
} elseif ($CapturedBcb) {
    throw "CapturedBcb not found: $CapturedBcb"
} else {
    Write-Host "[2/4] Rewriting the command field to '$BcbCommand'..." -ForegroundColor Cyan
    $bytes = [System.IO.File]::ReadAllBytes($backup)
    if ($bytes.Length -lt 32) { throw "misc dump is too small ($($bytes.Length) bytes). Check BcbSize / the partition name." }
    for ($i = 0; $i -lt 32; $i++) { $bytes[$i] = 0 }
    $cmdBytes = [System.Text.Encoding]::ASCII.GetBytes($BcbCommand)
    [Array]::Copy($cmdBytes, 0, $bytes, 0, $cmdBytes.Length)
    [System.IO.File]::WriteAllBytes($patched, $bytes)
}

# The BROM handshake only accepts one exchange per Download mode session, so
# sending write_part on the same session used for read_part fails with
# something like "ver expected". End the session and have the user
# re-enter Download mode.
Write-Host "[3/4] Disconnect the device from Download mode, then put it back into Download mode the normal way." -ForegroundColor Yellow
Read-Host "Press Enter once ready" | Out-Null

Write-Host "[4/4] Writing back misc and resetting the device into fastbootd..." -ForegroundColor Cyan
Invoke-SpdDump @("fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr, "write_part", $MiscPart, $patched, "reset")

Write-Host ""
Write-Host "Done. The device should be recognized by 'fastboot devices' within a few seconds." -ForegroundColor Green
Write-Host "The original misc content has been saved to $backup. If you get stuck and can't leave fastbootd, restore it with:" -ForegroundColor Yellow
Write-Host "  .\Enter-Fastbootd.ps1 -Fdl1 $Fdl1 -Fdl1Addr $Fdl1Addr -Fdl2 $Fdl2 -Fdl2Addr $Fdl2Addr -Restore" -ForegroundColor Yellow
