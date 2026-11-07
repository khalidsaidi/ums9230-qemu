import struct, capstone
p = '/home/khali/trustos-payload.bin'
d = bytearray(open(p,'rb').read())
BASE = 0xffffffffe0000000
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)

def bl(addr, tgt):
    off = (tgt - (BASE+addr)) >> 2
    return 0x94000000 | (off & 0x3ffffff)

def patch(addr, insns):
    """insns = list of (name, 32-bit encoding). Verifies with capstone."""
    for i, (name, enc) in enumerate(insns):
        d[addr+i*4 : addr+i*4+4] = struct.pack('<I', enc)
    print('patched 0x%x:' % (BASE+addr))
    for i in md.disasm(d[addr:addr+len(insns)*4], BASE+addr):
        print('  0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))

# 1. REVERT avb_memcpy (0x6e2e0) to plain memcpy+return0
patch(0x6e2e0, [
    ('stp', 0xA9BF7BFD),
    ('mov', 0x910003FD),
    ('bl',  bl(0x6e2e8, BASE+0x7e430)),
    ('mov', 0xD2800000),
    ('ldp', 0xA8C17BFD),
    ('ret', 0xD65F03C0),
])

# 2. read_rollback_index (0x37cf58): *out=0; return 0  (u-boot no-TEE equivalent)
patch(0x37cf58, [
    ('str xzr,[x2]', 0xF900005F),
    ('mov x0,#0',    0xD2800000),
    ('ret',          0xD65F03C0),
])

# 3. write_rollback_index (0x37cf98): return 0 (u-boot no-op)
patch(0x37cf98, [
    ('mov x0,#0', 0xD2800000),
    ('ret',       0xD65F03C0),
])

# 4. validate_vbmeta_public_key (0x8dff8): *out_is_trusted=true; return 0
patch(0x8dff8, [
    ('mov w1,#1',     0x52800021),
    ('strb w1,[x5]',  0x390000A1),
    ('mov x0,#0',     0xD2800000),
    ('ret',           0xD65F03C0),
])

open(p,'wb').write(d)
print('wrote payload')
