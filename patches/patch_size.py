import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
# 0x71560 "mov w1, #0x100000" -> "mov w1, #0xff" (255): 0x6ed70 rejects size > 0xff
d[0x71560:0x71564] = struct.pack('<I', 0x52801FE1)
for i in md.disasm(d[0x71560:0x71564], BASE+0x71560):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
