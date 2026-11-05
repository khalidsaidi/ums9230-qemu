import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())

# Patch 0x74f8c (storage-read wrapper): copy vbmeta into the caller's buffer, set *out = vbmeta.
# Args at entry: x0=ops, x1=buffer, x2=len(clobbered), x3=out, x5=offset(ignored).
# Save x30 across bl memcpy (memcpy clobbers x30); use x19 (caller no longer needs it after the read).
# Also force len = 0x1000 (x2 is being clobbered by the QEMU/trustos path).
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
    0xAA1E03F3,                                  # mov x19, x30  (save return addr)
    0xAA0103E0,                                  # mov x0, x1  (dst = buffer)
    enc_adrp(BASE+off+8,  vbmeta_va & ~0xfff, 1),# adrp x1, vbmeta_page
    0x91000021,                                  # add x1, x1, #0
    0x52820002,                                  # mov w2, #0x1000  (force len; x2 was clobbered)
    0xF9000061,                                  # str x1, [x3]  (*out = vbmeta)
    enc_bl(BASE+off+24, memcpy_va),              # bl memcpy
    0xAA1303FE,                                  # mov x30, x19  (restore return addr)
    0x52800000,                                  # mov w0, #0
    0xD65F03C0,                                  # ret
]
for i, ins in enumerate(insns):
    d[off + i*4 : off + i*4 + 4] = struct.pack('<I', ins)
open(p,'wb').write(d)
print('patched 0x74f8c (10 insns, x30 saved in x19, len forced 0x1000)')
