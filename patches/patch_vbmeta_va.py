import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)

# 0x74a4: "ldr x0, [x20, #0x158]" -> "adrp x0, 0xffffffffe0800000" (fixed vbmeta VA)
# ADRP imm21 = (0xffffffffe0800000 - (BASE+0x74a4 & ~0xfff)) >> 12
pc = BASE + 0x74a4
target = 0xffffffffe0800000
imm = (target - (pc & ~0xfff)) >> 12
immhi = (imm >> 2) & 0x7ffff
immlo = imm & 0x3
enc = 0x90000000 | (immlo << 29) | (immhi << 5) | 0
print('imm=0x%x immhi=0x%x immlo=0x%x enc=0x%x' % (imm, immhi, immlo, enc))
d[0x74a4:0x74a8] = struct.pack('<I', enc)
for i in md.disasm(d[0x74a0:0x74ac], BASE+0x74a0):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
open(p,'wb').write(d)
print('patched')
