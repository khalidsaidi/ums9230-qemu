import capstone, struct
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
def adrp(rd, target, pc):
    imm = (target - (pc & ~0xfff)) >> 12
    return 0x90000000 | ((imm & 0x3) << 29) | (((imm >> 2) & 0x7ffff) << 5) | rd
# 0x48e88: "ldr x1, [x20, #0x98]" -> "adrp x1, 0xffffffffe0800000" (img_addr)
d[0x8ff0:0x8ff4] = struct.pack('<I', adrp(1, 0xffffffffe0800000, BASE+0x8ff0))
# 0x48e88: "ldr x0, [x20, #0xa0]" -> "movz x0, #0x10, lsl #16" (img_size 0x100000)
d[0x9030:0x9034] = struct.pack('<I', 0xD2A00000 | (0x10 << 5) | 0)
for off in (0x8ff0, 0x9030):
    for i in md.disasm(d[off:off+4], BASE+off):
        print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
