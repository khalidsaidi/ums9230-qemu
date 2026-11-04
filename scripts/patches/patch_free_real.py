import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# patch 0x77e00: free -> ret (skip real heap free; fixed buffers aren't heap nodes)
d[0x77e00:0x77e04] = struct.pack('<I', 0xd65f03c0)  # ret
open(p,'wb').write(d)
print('patched 0x77e00 -> ret (skip heap free)')
