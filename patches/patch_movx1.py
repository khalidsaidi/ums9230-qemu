import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x71408: mov x19, x0  ->  mov x19, x1  (test: x1 mirror set in injection survives; bypasses x0 clobber)
d[0x71408:0x7140c] = struct.pack('<I', 0xaa0103f3)
open(p,'wb').write(d)
print('patched 0x71408 -> mov x19,x1')
