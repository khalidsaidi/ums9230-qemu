import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
def enc_b(addr, target):
    off = (target - (BASE+addr)) >> 2
    return 0x14000000 | (off & 0x3ffffff)
# dispatcher 0x799b0: ret -> b 0x79a84 (avb_slot_verify epilogue)
# avb_slot_verify 0x79a88: ret -> b 0x71574 (0x713f8 continuation)
patches = [(0x799b0, 0x79a84), (0x79a88, 0x71574)]
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
for addr, tgt in patches:
    enc = enc_b(addr, tgt)
    d[addr:addr+4] = struct.pack('<I', enc)
    i = list(md.disasm(struct.pack('<I', enc), BASE+addr))[0]
    print('0x%x: %-6s %s  (0x%08x)' % (BASE+addr, i.mnemonic, i.op_str, enc))
open(p,'wb').write(d)
print('done (kept 0x6f38c->b 0x799ac)')
