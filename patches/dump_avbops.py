import struct
d = open('/home/khali/trustos-payload.bin','rb').read()
BASE = 0xffffffffe0000000
PA = 0x80000000
# AvbOps at 0xffffffffe03548e0 (read_is_device_unlocked @ +0x30 = 0x354910)
ops = 0x3548e0
fields = ['read_from_partition','get_preloaded','write_to_partition','validate_vbmeta_public_key',
          'read_rollback_index','write_rollback_index','read_is_device_unlocked',
          'get_unique_guid','get_size_of_partition','read_permanent_attributes','hash']
for i, f in enumerate(fields):
    off = ops + i*8
    v = struct.unpack('<Q', d[off:off+8])[0]
    print('%02d %-28s @0x%x = 0x%x' % (i*8, f, BASE+off, v))
