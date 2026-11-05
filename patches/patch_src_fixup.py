import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
PA = 0x80000000

def enc_b(addr, target):
    off = (target - (BASE+addr)) >> 2
    assert -2**25 <= off < 2**25, hex(off)
    return 0x14000000 | (off & 0x3ffffff)

def enc_bl(addr, target):
    off = (target - (BASE+addr)) >> 2
    assert -2**25 <= off < 2**25, hex(off)
    return 0x94000000 | (off & 0x3ffffff)

def movz(rd, imm16, hw):
    return 0xD2800000 | (hw << 21) | (imm16 << 5) | rd

def mov(rd, rm):
    return 0xAA000000 | (rm << 16) | (31 << 5) | rd

def sub(rd, rn, rm):
    return 0xCB000000 | (rm << 16) | (rn << 5) | rd

HELPER_VA = BASE + 0x7f040   # 0xffffffffe007f040 (inside the mapped is_device_unlocked page)
HELPER_PA = 0x8007f040

insns = []
# helper: fix up src (x1 = x1 - 0x1fb00000 = x1 + (0xffffffffe0700000 - 0x200000)), then memcpy, return 0
insns.append(('mov x9, x30',        mov(9, 30)))            # save return addr (memcpy clobbers x30 via bl)
insns.append(('movz x3,0x1fb0<<16', movz(3, 0x1fb0, 1)))
insns.append(('sub x1,x1,x3',       sub(1, 1, 3)))
insns.append(('bl memcpy',          enc_bl(HELPER_VA-0xffffffffe0000000 + 0xc, BASE+0x7e430)))
insns.append(('mov x0,#0',          movz(0, 0, 0)))
insns.append(('mov x30,x9',         mov(30, 9)))
insns.append(('ret',                0xD65F03C0))

# patch 0x6e2e0 -> b helper
patch_insn = enc_b(0x6e2e0, HELPER_VA)

md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
helper_bytes = b''
for name, enc in insns:
    helper_bytes += struct.pack('<I', enc)
print('helper at 0x%x (%d bytes):' % (HELPER_VA, len(helper_bytes)))
for i in md.disasm(helper_bytes, HELPER_VA):
    print('  0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
print('patch 0x6e2e0: 0x%08x -> %s' % (patch_insn, [i.op_str for i in md.disasm(struct.pack('<I', patch_insn), BASE+0x6e2e0)][0]))
print('helper hex:', helper_bytes.hex())

# apply payload patch (0x6e2e0 -> b helper)
d[0x6e2e0:0x6e2e4] = struct.pack('<I', patch_insn)
open(p,'wb').write(d)

# write helper bytes to a file for the C injection
open('/home/khali/helper.bin','wb').write(helper_bytes)
print('wrote helper.bin + patched payload')
