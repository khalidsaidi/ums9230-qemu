import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x715a8: b 0x715a8 (error infinite loop) -> b 0x719a0 (sxtw x0,w19; ret) so it returns the result (3 = -11)
# offset 0x719a0 - 0x715a8 = 0x3f8 ; imm26 = 0x3f8>>2 = 0xfe
d[0x715a8:0x715ac] = struct.pack('<I', 0x14000000 | 0xfe)
open(p,'wb').write(d)
print('patched 0x715a8 -> b 0x719a0 (return result)')
