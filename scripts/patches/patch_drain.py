import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# drain (0x77fb8) -> ret (skip used-list reclamation)
d[0x77fb8:0x77fbc] = struct.pack('<I', 0xd65f03c0)
open(p,'wb').write(d)
print('patched 0x77fb8 -> ret (skip drain)')
