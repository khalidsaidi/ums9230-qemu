import struct
d = open('/home/khali/ums9230-qemu/firmware/vbmeta-stock.img','rb').read()
print('file size:', hex(len(d)))
# AvbVBMetaImageHeader (big-endian)
magic = d[0:4]
ver_major = struct.unpack('>I', d[4:8])[0]
ver_minor = struct.unpack('>I', d[8:12])[0]
auth_size = struct.unpack('>Q', d[0xc:0x14])[0]
aux_size = struct.unpack('>Q', d[0x14:0x1c])[0]
alg = struct.unpack('>I', d[0x1c:0x20])[0]
hash_off = struct.unpack('>Q', d[0x20:0x28])[0]
hash_sz = struct.unpack('>Q', d[0x28:0x30])[0]
sig_off = struct.unpack('>Q', d[0x30:0x38])[0]
sig_sz = struct.unpack('>Q', d[0x38:0x40])[0]
key_off = struct.unpack('>Q', d[0x40:0x48])[0]
key_sz = struct.unpack('>Q', d[0x48:0x50])[0]
meta_off = struct.unpack('>Q', d[0x50:0x58])[0]
meta_sz = struct.unpack('>Q', d[0x58:0x60])[0]
print('magic=%r major=%d minor=%d' % (magic, ver_major, ver_minor))
print('auth_size=0x%x aux_size=0x%x alg=%d' % (auth_size, aux_size, alg))
print('hash_off=0x%x hash_sz=0x%x sig_off=0x%x sig_sz=0x%x' % (hash_off, hash_sz, sig_off, sig_sz))
print('key_off=0x%x key_sz=0x%x meta_off=0x%x meta_sz=0x%x' % (key_off, key_sz, meta_off, meta_sz))
data_end = 0x100 + auth_size + aux_size
print('data_end (header+auth+aux) = 0x%x' % data_end)
print('footer addr = data_end = 0x%x (footer is 64 bytes at [data_end, data_end+0x40])' % data_end)
