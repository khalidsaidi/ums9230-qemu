import struct
p = 'build/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# patch print/printf (0x7e38c) -> ret, so the debug prints are no-ops
d[0x7e38c:0x7e390] = struct.pack('<I', 0xD65F03C0)
open(p,'wb').write(d)
print('patched print -> ret')
