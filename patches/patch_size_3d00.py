import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
# 0x71560: "mov w1, #0x100000" (was patched to #0xff) -> "mov w1, #0x3d00" (real vbmeta data size)
# movz w1, #0x3d00 = 0x52800000 | (0x3d00<<5) | 1
enc = 0x52800000 | (0x3d00 << 5) | 1
d[0x71560:0x71564] = struct.pack('<I', enc)
for i in md.disasm(d[0x71560:0x71564], BASE+0x71560):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
