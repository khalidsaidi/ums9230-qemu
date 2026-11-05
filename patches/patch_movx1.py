import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x71408: mov x19,x0 -> mov x19,x2  (x1 is clobbered by adrp x1 at 0x713fc)
d[0x71408:0x7140c] = struct.pack('<I', 0xAA0203F3)
open(p,'wb').write(d)
print('patched 0x71408 -> mov x19,x2')
