import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000

def enc_bl(addr, target):
    off = (target - (BASE+addr)) >> 2
    return 0x94000000 | (off & 0x3ffffff)

def movz(rd, imm16, hw):
    return 0xD2800000 | (hw << 21) | (imm16 << 5) | rd

def mov(rd, rm):
    return 0xAA000000 | (rm << 16) | (31 << 5) | rd

def sub(rd, rn, rm):
    return 0xCB000000 | (rm << 16) | (rn << 5) | rd

def ret(rm):
    return 0xD65F0000 | (rm << 5)

# in-place patch of read_from_partition (0x6e2e0, 6 insns):
insns = [
    (0x6e2e0, mov(9, 30)),              # mov x9, x30
    (0x6e2e4, movz(3, 0x1fb0, 1)),      # movz x3, #0x1fb0, lsl #16
    (0x6e2e8, sub(1, 1, 3)),            # sub x1, x1, x3
    (0x6e2ec, enc_bl(0x6e2ec, BASE+0x7e430)),  # bl memcpy
    (0x6e2f0, movz(0, 0, 0)),           # mov x0, #0
    (0x6e2f4, ret(9)),                  # ret x9
]

md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
print('in-place patch at 0x6e2e0:')
for addr, enc in insns:
    d[addr:addr+4] = struct.pack('<I', enc)
    i = list(md.disasm(struct.pack('<I', enc), BASE+addr))[0]
    print('  0x%x: %-8s %s  (0x%08x)' % (BASE+addr, i.mnemonic, i.op_str, enc))

open(p,'wb').write(d)
print('patched payload (no helper needed)')
