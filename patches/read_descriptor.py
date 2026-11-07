import struct
d = open('/home/khali/ums9230-qemu/firmware/vbmeta-stock.img','rb').read()
auth = d[0x100:0x100+0x240]
# hash descriptor = {image_size u64, hash_algorithm u32, digest_len u16, salt_len u16, digest, salt} big-endian
image_size = struct.unpack('>Q', auth[0:8])[0]
alg = struct.unpack('>I', auth[8:12])[0]
digest_len = struct.unpack('>H', auth[12:14])[0]
salt_len = struct.unpack('>H', auth[14:16])[0]
print('image_size=%d (0x%x)' % (image_size, image_size))
print('hash_algorithm=%d' % alg)
print('digest_len=%d salt_len=%d' % (digest_len, salt_len))
descriptor_size = 16 + digest_len + salt_len
print('descriptor size = 16 + %d + %d = %d (0x%x)' % (digest_len, salt_len, descriptor_size, descriptor_size))
print('digest (hex):', auth[16:16+digest_len].hex())
print('salt (hex):', auth[16+digest_len:16+digest_len+salt_len].hex() if salt_len else '(none)')
print('signature (first 8 bytes):', auth[0x20:0x28].hex())
