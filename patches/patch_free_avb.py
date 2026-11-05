import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x75a98 = avb free -> mov w0,#0; ret  (skip; ops free-list is not modeled)
d[0x75a98:0x75a9c] = struct.pack('<I', 0x52800000)
d[0x75a9c:0x75aa0] = struct.pack('<I', 0xD65F03C0)
open(p,'wb').write(d)
print('patched 0x75a98 free -> mov w0,#0; ret')
