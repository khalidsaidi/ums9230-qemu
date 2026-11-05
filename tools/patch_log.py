import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x3f300: bl 0x3f1f0 (error-log helper, calls garbage fn ptr 0x200) -> nop
d[0x3f300:0x3f304] = struct.pack('<I', 0xD503201F)
open(p,'wb').write(d)
print('patched 0x3f300 bl 0x3f1f0 -> nop')
