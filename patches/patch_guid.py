import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x71980: blr x6 (get_unique_guid_for_partition ops fn, unset) -> mov w0,#0
d[0x71980:0x71984] = struct.pack('<I', 0x52800000)
open(p,'wb').write(d)
print('patched 0x71980 blr x6 -> mov w0,#0')
