import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x71484: mov w2,#0x1000 -> mov w2,#0x100000  (read the full vbmeta so the aux/pk is present)
d[0x71484:0x71488] = struct.pack('<I', 0x52A00202)  # movz w2, #0x10, lsl #16
open(p,'wb').write(d)
print('patched 0x71484 -> mov w2,#0x100000')
