import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
# 0x714cc: cbz w23, 0x7150c -> NOP (always run the pubkey read so [x29+0x90] gets set)
d[0x714cc:0x714d0] = struct.pack('<I', 0xD503201F)
open(p,'wb').write(d)
print('patched 0x714cc cbz w23 -> nop')
