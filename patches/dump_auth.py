d = open('/home/khali/ums9230-qemu/firmware/vbmeta-stock.img','rb').read()
auth = d[0x100:0x100+0x240]
print('auth block first 0x60 bytes:')
for i in range(0, 0x60, 0x10):
    print('0x%03x: %s' % (i, auth[i:i+0x10].hex()))
print('printable:', repr(auth[:64]))
