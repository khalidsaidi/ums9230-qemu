import struct
d = open('/home/khali/ums9230-qemu/firmware/vbmeta-stock.img','rb').read()
print('len = 0x%x' % len(d))
# vbmeta header fields are big-endian in the image
def be32(off): return struct.unpack('>I', d[off:off+4])[0]
def be64(off): return struct.unpack('>Q', d[off:off+8])[0]
print('magic        =', d[0:4])
print('ver_major    =', be32(4))
print('ver_minor    =', be32(8))
print('header_size  =', be64(0xc))
print('auth_size    =', be64(0x10))
print('aux_size     =', be64(0x14))
print('algo_type    =', be32(0x1c))
print('hash_offset  =', be64(0x20))
print('hash_size    =', be64(0x28))
print('sig_offset   =', be64(0x30))
print('sig_size     =', be64(0x38))
print('pubkey_offset=', be64(0x40))
print('pubkey_size  =', be64(0x48))
