import capstone
d = open('/home/khali/trustos-payload.bin','rb').read()
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
BASE = 0xffffffffe0000000
for i in md.disasm(d[0x780dc:0x78220], BASE+0x780dc):
    print('0x%x: %-8s %s' % (i.address, i.mnemonic, i.op_str))
