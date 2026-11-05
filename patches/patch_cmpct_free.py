import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x783d0 cmpct_free -> ret (skip; bump allocator has no HEAP-magic header)
d[0x783d0:0x783d4] = struct.pack('<I', 0xD65F03C0)
open(p,'wb').write(d)
print('patched 0x783d0 cmpct_free -> ret')
