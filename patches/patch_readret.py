import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x75050: mov w0,w19 -> mov w0,#0  (x19 clobbered by iomap 0x3aac)
d[0x75050:0x75054] = struct.pack('<I', 0x52800000)
open(p,'wb').write(d)
print('patched 0x75050 -> mov w0,#0')
