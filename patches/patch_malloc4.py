import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
base = 0xffffffffe0000000

def adrp(rd, pc, target):
    pc_page = (pc & ~0xfff)
    off = (target - pc_page) >> 12
    off &= 0x1FFFFF
    if off & 0x100000:
        off -= 0x200000
    immlo = off & 0x3
    immhi = (off >> 2) & 0x7FFFF
    return 0x90000000 | (immlo << 29) | (immhi << 5) | rd

def add_imm(rd, rn, imm):
    return 0x91000000 | (imm << 10) | (rn << 5) | rd

# 0x780dc = miniheap malloc/memalign entry -> return fixed buffer 0xffffffffe060c500
buf = base + 0x60c500
off = 0x780dc
insns = [
    adrp(0, base+off,   buf & ~0xfff),
    add_imm(0, 0, buf & 0xfff),
    0xD65F03C0,  # ret
]
for i, ins in enumerate(insns):
    d[off+i*4:off+i*4+4] = struct.pack('<I', ins)
open(p,'wb').write(d)
print('patched 0x780dc miniheap malloc -> return 0xffffffffe060c500')
