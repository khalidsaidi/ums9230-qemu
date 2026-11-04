import struct
p = 'build/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
base = 0xffffffffe0000000

def adrp(rd, pc, target):
    pc_page = pc & ~0xfff
    off = (target - pc_page) >> 12
    off &= 0x1FFFFF
    if off & 0x100000: off -= 0x200000
    return 0x90000000 | ((off & 3) << 29) | ((off >> 2 & 0x7FFFF) << 5) | rd

# idle loop: capture x0 (the verify return) into [0xffffffffe060b000] before wfi loop
d[0x1888:0x188c] = struct.pack('<I', adrp(2, base+0x1888, base+0x60b000))  # adrp x2,#0xffffffffe060b000
d[0x188c:0x1890] = struct.pack('<I', 0xF9000040)  # str x0,[x2]
d[0x1890:0x1894] = struct.pack('<I', 0x14000000 | ((-3) & 0x3FFFFFF))  # b #0x1884
open(p,'wb').write(d)
print('idle loop patched to capture x0')
