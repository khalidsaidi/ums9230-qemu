import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
# 0x48e88 "mov x0, #0x100000" -> "mov x0, #0x3d00" (img_size = data size)
d[0x9030:0x9034] = struct.pack('<I', 0x52800000 | (0x3d00 << 5) | 0)
for i in md.disasm(d[0x9030:0x9034], BASE+0x9030):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
