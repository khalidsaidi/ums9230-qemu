import struct, capstone
p = 'build/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
base = 0xffffffffe0000000

def adrp(rd, pc, target):
    pc_page = (pc & ~0xfff)
    off = (target - pc_page) >> 12
    off &= 0x1FFFFF  # 21-bit
    if off & 0x100000:
        off -= 0x200000  # sign extend
    immlo = off & 0x3
    immhi = (off >> 2) & 0x7FFFF
    return 0x90000000 | (immlo << 29) | (immhi << 5) | rd

def add_imm(rd, rn, imm):
    return 0x91000000 | (imm << 10) | (rn << 5) | rd

NOP = 0xD503201F
buf_page = base + 0x60c000  # 0xffffffffe060c000

# patch the three malloc sequences in avb_vbmeta_image_verify (0x6ed70)
# malloc(0x100) -> x21 ; malloc(0xd0) -> x19 ; malloc(0x190) -> x20
patches = [
    (0x6edb0, NOP),                       # mov x0,#0x100 -> nop
    (0x6edb4, adrp(21, base+0x6edb4, buf_page)),  # bl malloc -> adrp x21
    (0x6edb8, add_imm(21,21,0)),          # mov x21,x0 -> add x21,x21,#0
    (0x6edbc, NOP),                       # mov x0,#0xd0 -> nop
    (0x6edc0, adrp(19, base+0x6edc0, buf_page)),  # bl malloc -> adrp x19
    (0x6edc4, add_imm(19,19,0x200)),      # mov x19,x0 -> add x19,x19,#0x200
    (0x6edc8, NOP),                       # mov x0,#0x190 -> nop
    (0x6edcc, adrp(20, base+0x6edcc, buf_page)),  # bl malloc -> adrp x20
    (0x6edd0, add_imm(20,20,0x400)),      # mov x20,x0 -> add x20,x20,#0x400
]
for off, ins in patches:
    d[off:off+4] = struct.pack('<I', ins)

open(p,'wb').write(d)

# verify
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
for i in md.disasm(d[0x6edb0:0x6edd4], base+0x6edb0):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
print('patched')
