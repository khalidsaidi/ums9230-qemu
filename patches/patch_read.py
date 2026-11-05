import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())

# Patch 0x74f8c (storage-read wrapper) to serve the vbmeta from RAM:
#   memcpy(buffer, vbmeta_va, len);  *out = vbmeta_va;  return 0.
# At entry: x1=buffer, x2=len, x3=out, x5=offset(ignored).
BASE = 0xffffffffe0000000
vbmeta_va = 0xffffffffe0700000
memcpy_va = 0xffffffffe007e430   # memcpy(dst=x0, src=x1, len=x2)

def enc_adrp(pc, target_page, rd):
    imm = ((target_page - (pc & ~0xfff)) >> 12) & 0x1FFFFF
    return 0x90000000 | ((imm & 3) << 29) | ((imm >> 2) << 5) | rd

def enc_bl(pc, target):
    imm = ((target - pc) >> 2) & 0x3FFFFFF
    return 0x94000000 | imm

off = 0x74f8c
insns = [
    0xAA0103E0,                                  # mov x0, x1  (dst = buffer)
    enc_adrp(BASE+off+4, vbmeta_va & ~0xfff, 1), # adrp x1, vbmeta_page
    0x91000021,                                  # add x1, x1, #0 (page aligned)
    enc_bl(BASE+off+12, memcpy_va),              # bl memcpy
    0xF9000061,                                  # str x1, [x3]  (*out = vbmeta)
    0x52800000,                                  # mov w0, #0
    0xD65F03C0,                                  # ret
]
for i, ins in enumerate(insns):
    d[off + i*4 : off + i*4 + 4] = struct.pack('<I', ins)
open(p,'wb').write(d)
print('patched 0x74f8c -> memcpy vbmeta + set *out (', len(insns), 'insns)')
