import struct
d = open('/home/khali/trustos-payload.bin','rb').read()
def rd64(va):
    off = va - 0xffffffffe0000000
    return struct.unpack('<Q', d[off:off+8])[0]
for va in (0xffffffffe0354058, 0xffffffffe03544a8, 0xffffffffe0354610,
           0xffffffffe0354640, 0xffffffffe03548c0, 0xffffffffe03546a0,
           0xffffffffe0354540, 0xffffffffe0354530):
    print('0x%x = 0x%x' % (va, rd64(va)))
print('--- deref pointers ---')
for g in (0xffffffffe0354058, 0xffffffffe0354610, 0xffffffffe03548c0, 0xffffffffe03544a8):
    p = rd64(g)
    val = rd64(p) if 0x80000000 <= p < 0x80000000+len(d) else 0
    print('global 0x%x -> ptr 0x%x -> *0x%x' % (g, p, val))
