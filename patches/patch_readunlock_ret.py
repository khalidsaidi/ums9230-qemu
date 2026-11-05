import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# The "blr x3" (indirect call) clobbers x30 to 0 in this TCG build.
# Force read_is_device_unlocked's epilogue to return to the dispatcher's continuation 0x799ac.
d[0x6f38c:0x6f390] = struct.pack('<I', 0x14002988)  # b 0x799ac
open(p,'wb').write(d)
print('patched 0x6f38c ret -> b 0x799ac')
