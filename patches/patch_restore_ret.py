import struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
RET = 0xD65F03C0
# restore the two dispatcher-chain "ret"s that were over-patched
d[0x799b0:0x799b4] = struct.pack('<I', RET)   # 0x799b0: b 0x79a84 -> ret
d[0x79a88:0x79a8c] = struct.pack('<I', RET)   # 0x79a88: b 0x71574 -> ret
open(p,'wb').write(d)
print('restored 0x799b0 + 0x79a88 to ret (kept 0x6f38c->b 0x799ac + memcpy fixup)')
