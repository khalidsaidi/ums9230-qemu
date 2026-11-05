<#
.SYNOPSIS
    Read-only dump of spl_a / uboot_a (and, for comparison, spl_b / uboot_b)
    from Download mode.

.DESCRIPTION
    A read-only reconnaissance step for investigating whether
    unisoc_chipram_signcheck_exploit (a persistent bypass of the SPL/FDL1
    signature check) could work on this device. Performs no writes at all.

.EXAMPLE
    .\Dump-Boot.ps1
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

$out = Join-Path $PSScriptRoot "boot_dump"
New-Item -ItemType Directory -Force -Path $out | Out-Null

# partition-size: spl_a/spl_b = 0x400000 (4MB), uboot_a/uboot_b = 0x300000 (3MB)
$targets = @(
    @{ Part = "spl_a";   Size = "0x400000"; File = "spl_a.bin" },
    @{ Part = "spl_b";   Size = "0x400000"; File = "spl_b.bin" },
    @{ Part = "uboot_a"; Size = "0x300000"; File = "uboot_a.bin" },
    @{ Part = "uboot_b"; Size = "0x300000"; File = "uboot_b.bin" }
)

$spdArgs = @("fdl", $Fdl1, $Fdl1Addr, "fdl", $Fdl2, $Fdl2Addr)
foreach ($t in $targets) {
    $f = Join-Path $out $t.File
    $spdArgs += @("read_part", $t.Part, "0", $t.Size, $f)
}

Write-Host "Connecting to Download mode and reading spl_a/spl_b/uboot_a/uboot_b (read-only)..." -ForegroundColor Cyan
Write-Host ">> $SpdDump $($spdArgs -join ' ')" -ForegroundColor DarkGray
& $SpdDump @spdArgs
if ($LASTEXITCODE -ne 0) { throw "spd_dump exited with an error (exit $LASTEXITCODE)." }

Write-Host ""
Write-Host "Done. Saved to $out." -ForegroundColor Green
