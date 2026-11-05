import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x78d80: blr x21 (vsnprintf output fn, x21=NULL) -> mov w0,#0
d[0x78d80:0x78d84] = struct.pack('<I', 0x52800000)
open(p,'wb').write(d)
print('patched 0x78d80 blr x21 -> mov w0,#0')
