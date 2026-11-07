import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
def adrp(rd, target, pc):
    imm = (target - (pc & ~0xfff)) >> 12
    return 0x90000000 | ((imm & 0x3) << 29) | (((imm >> 2) & 0x7ffff) << 5) | rd
# patch the two 0x7464 loads [x20,#0x158] to fixed vbmeta VA
for off in (0x74a4, 0x74c4):
    pc = BASE + off
    d[off:off+4] = struct.pack('<I', adrp(0, 0xffffffffe0800000, pc))
for off in (0x74a4, 0x74c4):
    for i in md.disasm(d[off:off+4], BASE+off):
        print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
