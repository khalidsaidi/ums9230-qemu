import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())

# avb_slot_verify (0x713f8) calls avb_vbmeta_image_verify with x0=[x29+0x70], w1=w24.
# [x29+0x70] is set by a storage read gated on a header field that is 0 for the stock vbmeta,
# and w24 (the size) is read from the same 0 field. Point x0 at the vbmeta we already loaded
# (via [x29+0x98], which the first read fills) and force the size to the full 1MB image.

# 0x7155c: ldr x0, [x29, #0x70] -> ldr x0, [x29, #0x98]
d[0x7155c:0x71560] = struct.pack('<I', 0xF9404BA0)
# 0x71560: mov w1, w24 -> movz w1, #0x10, lsl #16  (= 0x100000)
d[0x71560:0x71564] = struct.pack('<I', 0x52A00201)
open(p,'wb').write(d)
print('patched 0x7155c/0x71560 -> vbmeta ptr + size 0x100000')
