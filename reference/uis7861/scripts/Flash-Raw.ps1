<#
.SYNOPSIS
    Generic script to write an arbitrary .img directly to an arbitrary partition
    from Download mode (BROM+FDL).

.DESCRIPTION
    Uses spd_dump's write_part directly, without going through fastbootd.
    For a physical (raw) partition like "super", no fastbootd-style logical
    partition operations (delete/create-logical-partition) are needed at all --
    writing back the whole super.img restores system_a/vendor_a/product_a/...
    and the LP metadata (including cow reservations) inside it all at once.

    Useful for (partially) re-flashing a stock ROM when the PAC is broken and
    only individual .img files are available.

    The partition names you write to must match the names listed under
    <Partitions> in the device's partition XML (e.g. super, boot_a,
    vendor_boot_a, vbmeta_a, dtbo_a, system_a, vendor_a, product_a, etc.).
    Don't forget the "_a" / "_b" suffix for A/B slot partitions.

    About the -Unsigned switch:
    A stock (signed) fdl2-sign.bin verifies the signature of the write_part
    data itself, and silently rejects writing a modified image to a protected
    partition such as uboot_a/uboot_b regardless of its content (the write
    fails because no ACK comes back for the final chunk).
    Specifying -Unsigned bypasses BROM's signature verification every session
    via CVE-2022-38694 (exec_addr/loadexec), and writes through the unsigned
    fdl1-dl.bin/fdl2-dl.bin instead.
    This is required when writing a modified image to uboot_a/uboot_b. It is
    not required for unprotected partitions such as vbmeta_*/misc (but does
    no harm if used anyway).

.EXAMPLE
    # Write back super.img only, then reset
    .\Flash-Raw.ps1 -Files "super=D:\firmware\super.img"

.EXAMPLE
    # Write multiple partitions in a single Download mode session
    .\Flash-Raw.ps1 -Files @(
        "super=D:\firmware\super.img",
        "vbmeta_a=D:\firmware\vbmeta.img",
        "vbmeta_system_a=D:\firmware\vbmeta_system.img",
        "boot_a=D:\firmware\boot.img"
    )

.EXAMPLE
    # Don't reset after writing (if you want to keep doing other operations)
    .\Flash-Raw.ps1 -Files "super=D:\firmware\super.img" -NoReset

.EXAMPLE
    # Write a modified image to uboot_a/uboot_b (signature bypass required)
    .\Flash-Raw.ps1 -Unsigned -Files @(
        "uboot_a=.\boot_dump\uboot_a_patched_trunc.bin",
        "uboot_b=.\boot_dump\uboot_b_patched_trunc.bin"
    )
#>

param(
    [string]$SpdDump  = ".\spd_dump.exe",
    [string]$Fdl1     = ".\fdl1-sign.bin",
    [string]$Fdl1Addr = "0x65000800",
    [string]$Fdl2     = ".\fdl2-sign.bin",
    [string]$Fdl2Addr = "0x9EFFFE00",
    # Specify one or more entries in "partition-name=file-path" form
    [Parameter(Mandatory=$true)][string[]]$Files,
    [switch]$NoReset,
    # A signed fdl2-sign.bin verifies the signature of the write_part data itself,
    # and effectively fails the write for a modified image by never returning an
    # ACK for the final chunk (see load_partition() in the spd_dump source:
    # "signature verification ... failed or timeout reached").
    # Specifying -Unsigned bypasses BROM's signature verification every session
    # via CVE-2022-38694 (exec_addr), and uses the unsigned fdl1-dl.bin/fdl2-dl.bin
    # instead.
    [switch]$Unsigned,
    [string]$ExecAddr    = "0x65015f08",
    [string]$CustomExec  = ".\custom_exec_no_verify_65015f08.bin",
    [string]$Fdl1Unsigned = ".\fdl1-dl.bin",
    [string]$Fdl2Unsigned = ".\fdl2-dl.bin"
)

$ErrorActionPreference = "Stop"

if ($Unsigned -and -not $PSBoundParameters.ContainsKey('SpdDump')) {
    # The regular spd_dump.exe build does not support exec_addr/loadexec, so
    # default to the libusb build (spd_dump_dl.exe), which does support them.
    $SpdDump = ".\spd_dump_dl.exe"
}

if ($Unsigned) {
    if (-not (Test-Path $CustomExec))    { throw "custom_exec file not found: $CustomExec" }
    if (-not (Test-Path $Fdl1Unsigned))  { throw "Unsigned FDL1 not found: $Fdl1Unsigned" }
    if (-not (Test-Path $Fdl2Unsigned))  { throw "Unsigned FDL2 not found: $Fdl2Unsigned" }
    $Fdl1 = $Fdl1Unsigned
    $Fdl2 = $Fdl2Unsigned
}

if (-not (Test-Path $SpdDump)) { throw "spd_dump.exe not found: $SpdDump" }
if (-not (Test-Path $Fdl1))    { throw "FDL1 not found: $Fdl1" }
if (-not (Test-Path $Fdl2))    { throw "FDL2 not found: $Fdl2" }

$pairs = @()
foreach ($entry in $Files) {
    $idx = $entry.IndexOf("=")
    if ($idx -lt 1) { throw "Invalid Files entry (expected partition-name=path): $entry" }
    $part = $entry.Substring(0, $idx)
    $path = $entry.Substring($idx + 1)
    if (-not (Test-Path $path)) { throw "File not found: $path (partition: $part)" }
    $size = (Get-Item $path).Length
    Write-Host ("  {0,-20} <- {1} ({2:N1} MiB)" -f $part, $path, ($size/1MB)) -ForegroundColor Cyan
    $pairs += , @($part, $path)
}

Write-Host ""
Write-Host "The following will be written from Download mode:" -ForegroundColor Cyan
$ans = Read-Host "Proceed? [y/N]"
if ($ans -notin @("y","Y","yes","Yes")) { throw "Aborted." }

if ($Unsigned) {
    $spdArgs = @("loadexec", $CustomExec, "fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr, "exec")
} else {
    $spdArgs = @("fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr)
}
foreach ($p in $pairs) {
    $spdArgs += @("write_part", $p[0], $p[1])
}
if (-not $NoReset) { $spdArgs += @("reset") }

Write-Host ""
Write-Host "Connecting to Download mode and starting the write (large files take a while)..." -ForegroundColor Cyan
Write-Host ">> $SpdDump $($spdArgs -join ' ')" -ForegroundColor DarkGray
& $SpdDump @spdArgs
if ($LASTEXITCODE -ne 0) { throw "spd_dump exited with an error (exit $LASTEXITCODE)." }

Write-Host ""
Write-Host "Done." -ForegroundColor Green
if (-not $NoReset) { Write-Host "The device has been reset." -ForegroundColor Green }
