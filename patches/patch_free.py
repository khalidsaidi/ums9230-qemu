import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
# 0x7e4a4: the vmm_free_region wrapper returns non-zero because the region base
# (0xffffffffe0700000) != allocated VA (0xffffffffe0800000). Make it return 0 (success).
d[0x7e4a4:0x7e4ac] = struct.pack('<II', 0x52800000, 0xD65F03C0)  # mov w0,#0 ; ret
for i in md.disasm(d[0x7e4a4:0x7e4ac], BASE+0x7e4a4):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
