import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# patch 0x2918: mrs x0, dbgauthstatus_el1 -> mov x0, #0 (debug disabled)
ins = 0xd2800000  # mov x0, #0
d[0x2918:0x291c] = struct.pack('<I', ins)
open(p,'wb').write(d)
print('patched 0x2918 -> mov x0,#0')
