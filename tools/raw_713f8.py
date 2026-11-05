import struct
d = open('/home/khali/trustos-payload.bin','rb').read()
BASE = 0xffffffffe0000000
for off in (0x713f8, 0x713fc, 0x71400, 0x71404, 0x71408):
    w = struct.unpack('<I', d[off:off+4])[0]
    print('0x%x: raw=0x%08x' % (BASE+off, w))
