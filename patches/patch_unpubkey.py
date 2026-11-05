import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# revert patch_pubkey: 0x714cc nop -> cbz w23, 0x7150c  (skip the pubkey read; its offset is raw big-endian)
# cbz w23, +0x40 => imm19 = 0x10 ; 0xB4000000 | (0x10<<5) | 23
d[0x714cc:0x714d0] = struct.pack('<I', 0xB4000000 | (0x10 << 5) | 23)
open(p,'wb').write(d)
print('reverted 0x714cc -> cbz w23, 0x7150c')
