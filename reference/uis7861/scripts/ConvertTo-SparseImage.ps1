<#
.SYNOPSIS
    Convert a raw image to the Android sparse format (minimal img2simg equivalent).

.DESCRIPTION
    This build of fastboot (36.0.2) has a bug where, when sending a raw file
    larger than max-download-size, its automatic sparse-splitting fails with
    "Invalid sparse file format at header magic" / "Error reading sparse file".

    Pre-converting to a proper sparse image works around this, because
    fastboot then takes the well-tested sparse->sparse re-splitting path
    instead of the buggy raw->sparse auto-conversion path.

    As a minimal implementation, this performs no compression (e.g. no
    detection of zero-filled regions): it just wraps the entire file as a
    single "raw chunk" inside one sparse image (a valid sparse format, but
    roughly the same size as the original raw file). If the input file size
    is not a multiple of blk_sz (default 4096), it is automatically
    zero-padded.

    Note: PowerShell interprets hex literals of 0x80000000 or greater (e.g.
    0xED26FF3A) as signed 32-bit integers, turning them negative. To avoid
    this trap, every header field here is manually assembled into
    little-endian bytes using [int64] decimal arithmetic and bit shifts
    (no cast to [uint32]/[uint16] is used anywhere).

.EXAMPLE
    .\ConvertTo-SparseImage.ps1 -InFile .\system.img -OutFile .\system.sparse.img
#>

param(
    [Parameter(Mandatory=$true)][string]$InFile,
    [Parameter(Mandatory=$true)][string]$OutFile,
    [int64]$BlockSize = 4096
)

$ErrorActionPreference = "Stop"
if (-not (Test-Path $InFile)) { throw "Input file not found: $InFile" }

function Get-LE32 {
    param([int64]$v)
    if ($v -lt 0 -or $v -gt 4294967295) { throw "Value out of uint32 range: $v" }
    $b = New-Object byte[] 4
    $b[0] = [byte]($v -band 0xFF)
    $b[1] = [byte](($v -shr 8) -band 0xFF)
    $b[2] = [byte](($v -shr 16) -band 0xFF)
    $b[3] = [byte](($v -shr 24) -band 0xFF)
    return $b
}
function Get-LE16 {
    param([int64]$v)
    if ($v -lt 0 -or $v -gt 65535) { throw "Value out of uint16 range: $v" }
    $b = New-Object byte[] 2
    $b[0] = [byte]($v -band 0xFF)
    $b[1] = [byte](($v -shr 8) -band 0xFF)
    return $b
}

[int64]$rawSize = (Get-Item $InFile).Length
[int64]$rem = $rawSize % $BlockSize
[int64]$padBytes = 0
if ($rem -ne 0) { $padBytes = $BlockSize - $rem }
[int64]$inSize = $rawSize + $padBytes
[int64]$totalBlocks = $inSize / $BlockSize
[int64]$chunkTotalSz = 12 + $inSize

if ($padBytes -gt 0) {
    Write-Host "Adding $padBytes bytes of zero padding to align to a $BlockSize-byte boundary" -ForegroundColor Yellow
}
Write-Host "Converting: $InFile ($rawSize bytes -> $inSize bytes, $totalBlocks blocks) -> $OutFile" -ForegroundColor Cyan

$fsIn = [System.IO.File]::OpenRead($InFile)
$fsOut = [System.IO.File]::Create($OutFile)
try {
    # --- sparse_header (28 bytes, little-endian) ---
    # magic = 0xED26FF3A = 3978755898 (given in decimal, since the hex literal
    # would be trapped as a signed 32-bit value -- see the note above)
    $fsOut.Write((Get-LE32 3978755898), 0, 4)  # magic
    $fsOut.Write((Get-LE16 1), 0, 2)            # major_version
    $fsOut.Write((Get-LE16 0), 0, 2)            # minor_version
    $fsOut.Write((Get-LE16 28), 0, 2)           # file_hdr_sz
    $fsOut.Write((Get-LE16 12), 0, 2)           # chunk_hdr_sz
    $fsOut.Write((Get-LE32 $BlockSize), 0, 4)   # blk_sz
    $fsOut.Write((Get-LE32 $totalBlocks), 0, 4) # total_blks
    $fsOut.Write((Get-LE32 1), 0, 4)            # total_chunks (everything as a single raw chunk)
    $fsOut.Write((Get-LE32 0), 0, 4)            # image_checksum (unused)

    # --- chunk_header (12 bytes, little-endian): CHUNK_TYPE_RAW ---
    # chunk_type = 0xCAC1 = 51905 (below 0x80000000 so the hex literal would be
    # fine as-is, but kept in decimal for consistency with the fields above)
    $fsOut.Write((Get-LE16 51905), 0, 2)        # chunk_type = raw
    $fsOut.Write((Get-LE16 0), 0, 2)            # reserved1
    $fsOut.Write((Get-LE32 $totalBlocks), 0, 4) # chunk_sz (blocks)
    $fsOut.Write((Get-LE32 $chunkTotalSz), 0, 4)# total_sz (header + data, bytes)

    # --- stream-copy the raw data (rawSize bytes) ---
    $buf = New-Object byte[] (16 * 1024 * 1024)
    [int64]$remaining = $rawSize
    while ($remaining -gt 0) {
        $toRead = [Math]::Min([int64]$buf.Length, $remaining)
        $read = $fsIn.Read($buf, 0, [int]$toRead)
        if ($read -le 0) { throw "Input file read ended prematurely." }
        $fsOut.Write($buf, 0, $read)
        $remaining -= $read
    }
    # --- zero-pad the remainder ---
    if ($padBytes -gt 0) {
        $zeros = New-Object byte[] $padBytes
        $fsOut.Write($zeros, 0, $padBytes)
    }
}
finally {
    $fsIn.Close()
    $fsOut.Close()
}

Write-Host "Done: $OutFile ($((Get-Item $OutFile).Length) bytes)" -ForegroundColor Green

# Return the padded size (the raw byte count once unpacked) so callers can use
# it directly for sizing create-logical-partition.
Write-Output $inSize
