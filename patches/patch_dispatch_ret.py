import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# dispatcher 0x79984's ret (0x799b0) -> b 0x79a84 (forced return to 0x79a14's caller)
# this is the read_is_device_unlocked wrapper path
d[0x799b0:0x799b4] = struct.pack('<I', 0x14000035)  # b 0x79a84
open(p,'wb').write(d)
print('patched 0x799b0 ret -> b 0x79a84')
