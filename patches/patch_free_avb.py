import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x75a98 = avb free -> ret (skip; ops free-list is not modeled)
d[0x75a98:0x75a9c] = struct.pack('<I', 0xD65F03C0)
open(p,'wb').write(d)
print('patched 0x75a98 free -> ret')
