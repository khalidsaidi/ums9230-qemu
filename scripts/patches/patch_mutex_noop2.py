import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# mutex_acquire_timeout (0x39ad4) -> mov w0,#0 ; ret
d[0x39ad4:0x39ad8] = struct.pack('<I', 0x52800000)
d[0x39ad8:0x39adc] = struct.pack('<I', 0xd65f03c0)
# mutex_release (0x39c30) -> mov w0,#0 ; ret
d[0x39c30:0x39c34] = struct.pack('<I', 0x52800000)
d[0x39c34:0x39c38] = struct.pack('<I', 0xd65f03c0)
open(p,'wb').write(d)
print('patched mutex_acquire_timeout(0x39ad4) + mutex_release(0x39c30) -> no-op')
