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

# 0x780dc = cmpct_memalign/malloc -> bump allocator.
# bump pointer stored at 0xffffffffe060d180 (PA 0x8060d180), base set by injection.
bump_ptr = base + 0x60d180
off = 0x780dc
insns = [
    adrp(1, base+off,   bump_ptr & ~0xfff),   # adrp x1, bump_ptr_page
    add_imm(1, 1, bump_ptr & 0xfff),         # add x1, x1, #0x180
    0xF9400022,                               # ldr x2, [x1]     (cur bump)
    0x91010000,                               # add x0, x0, #0x40 (size + hdr/align)
    0x8B000043,                               # add x3, x2, x0    (new bump)
    0xF9000023,                               # str x3, [x1]     (save)
    0xAA0203E0,                               # mov x0, x2        (return old)
    0xD65F03C0,                               # ret
]
for i, ins in enumerate(insns):
    d[off+i*4:off+i*4+4] = struct.pack('<I', ins)
open(p,'wb').write(d)
print('patched 0x780dc -> bump allocator')
