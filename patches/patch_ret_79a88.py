import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000

def patch_b(addr, target):
    off = (target - (BASE+addr)) >> 2
    insn = 0x14000000 | (off & 0x3ffffff)
    d[addr:addr+4] = struct.pack('<I', insn)
    print('0x%x: b 0x%x -> 0x%08x' % (addr, target, insn))

# 0x79a88: ret -> b 0x71574 (0x713f8 continuation after bl 0x6ed70)
patch_b(0x79a88, BASE + 0x71574)

open(p,'wb').write(d)
print('patched', p)
