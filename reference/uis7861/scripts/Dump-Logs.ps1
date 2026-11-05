<#
.SYNOPSIS
    Dump the uboot_log / sysdumpdb partitions from Download mode.

.DESCRIPTION
    A diagnostic script for checking whether any bootloader/kernel log
    information survives, on a device with no UART access.
    Both are single physical partitions (not A/B).

.EXAMPLE
    .\Dump-Logs.ps1
#>

param(
    [string]$SpdDump  = ".\spd_dump.exe",
    [string]$Fdl1     = ".\fdl1-sign.bin",
    [string]$Fdl1Addr = "0x65000800",
    [string]$Fdl2     = ".\fdl2-sign.bin",
    [string]$Fdl2Addr = "0x9EFFFE00"
)

$ErrorActionPreference = "Stop"
if (-not (Test-Path $SpdDump)) { throw "spd_dump.exe not found: $SpdDump" }
if (-not (Test-Path $Fdl1))    { throw "FDL1 not found: $Fdl1" }
if (-not (Test-Path $Fdl2))    { throw "FDL2 not found: $Fdl2" }

$out = Join-Path $PSScriptRoot "logs"
New-Item -ItemType Directory -Force -Path $out | Out-Null
$ubootLog  = Join-Path $out "uboot_log.bin"
$sysdumpdb = Join-Path $out "sysdumpdb.bin"

# partition-size:uboot_log:0x400000 (4MB), partition-size:sysdumpdb:0xA00000 (10MB)
$spdArgs = @(
    "fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr,
    "read_part", "uboot_log", "0", "0x400000", $ubootLog,
    "read_part", "sysdumpdb", "0", "0xA00000", $sysdumpdb
)

Write-Host "Connecting to Download mode and reading uboot_log and sysdumpdb..." -ForegroundColor Cyan
Write-Host ">> $SpdDump $($spdArgs -join ' ')" -ForegroundColor DarkGray
& $SpdDump @spdArgs
if ($LASTEXITCODE -ne 0) { throw "spd_dump exited with an error (exit $LASTEXITCODE)." }

Write-Host ""
Write-Host "Done. Saved to:" -ForegroundColor Green
Write-Host "  $ubootLog"
Write-Host "  $sysdumpdb"
Write-Host ""
Write-Host "Check for any readable text in them, e.g.:" -ForegroundColor Yellow
Write-Host "  Select-String -Path $ubootLog -Pattern '[-a-zA-Z0-9_./: ]{6,}' | Select-Object -First 50"
