import struct
p = 'build/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# patch free (0x6e330: b #0x7e45c) -> ret, so freeing our fixed buffers is a no-op
d[0x6e330:0x6e334] = struct.pack('<I', 0xD65F03C0)
open(p,'wb').write(d)
print('patched free -> ret')
