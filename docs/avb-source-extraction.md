# AVB verified-boot — source extraction (from cloned repos)

Authoritative source: `tmp-repos/SL8541E-BootChain/原厂启动链-vp19/TrustOS/trustos-pseudo.c`
plus `tmp-repos/avb/libavb/*`.

## 1. Function identity (CORRECTION)
- `0x940446DC load_and_verify_vbmeta` (size 4620) == our **0x713f8**.
  It is NOT `avb_slot_verify`. It does the single-partition read + verify + result mapping.
- `0x940459C4 avb_slot_verify` (size 2384) is the HIGHER-level lib function:
  `avb_calloc(304/1024/768)` then calls `load_and_verify_vbmeta` twice
  (once for "vbmeta", once for the descriptor-chained partition), ORs the results, returns.
- `0x940471B4 avb_read_from_partition` (size 408) == the storage-read ops fn.
- `0x94046B5C avb_vbmeta_verify` (size 1268) == our **0x6ed70**.

## 2. load_and_verify_vbmeta result mapping (the switch)
```
v48 = MEMORY[0xFFFFFFFFE0064408];      // vbmeta size
v49 = avb_malloc(v48);
if (!v49) return 1;                     // OOM
v58 = (*(ops+24))(ops, name, offset, v48, v49, &num_read);  // read_from_partition
if (v58 == 1) return 1;
if (v58 != 0) return 2;
v375 = avb_vbmeta_verify(v49, num_read, &pk_data, &pk_len, 0);
switch (v375):
  case 0:              return 0;        // OK
  case 1: case 4: case 5: return 3;     // NOT_SIGNED / HASH_MISMATCH / SIG_MISMATCH -> 3
  case 2:              return 6;        // INVALID_VBMETA_HEADER -> 6
  case 3:              return 7;        // UNSUPPORTED_VERSION -> 7
  default:             return 0;
```
So: **valid -> 0**, **version=2 -> verify returns 3 -> mapped to 7** (NOT 3, NOT -11).

Verify result enum (`avb_vbmeta_verify_result_to_string @ 0x94047050`):
`0 OK, 1 OK_NOT_SIGNED, 2 INVALID_VBMETA_HEADER, 3 UNSUPPORTED_VERSION, 4 HASH_MISMATCH, 5 SIGNATURE_MISMATCH`.

## 3. Storage read (the ops fn we patched) — REAL code
```
avb_read_from_partition(ops, name, offset, size, buf, &num_read):
  if strcmp(name,"vbmeta") != 0: v19 = MEMORY[0xFFFFFFFFE0064404]   # img_size
  else:                          v19 = MEMORY[0xFFFFFFFFE0064408]   # vbmeta_img_size
  # offset-in-range check -> return 4 on out-of-range
  if strcmp(name,"vbmeta") != 0: memcpy(buf, MEMORY[0xFFFFFFFFE00643D8] + offset, size)
  else: memcpy(buf, MEMORY[0xFFFFFFFFE00643E0] + offset, size)      # vbmeta_img_addr
        memcpy(0xE0010000, MEMORY[0xFFFFFFFFE00643E0] + offset, size)  # save for cp verify
  *num_read = size
  return 0
```
So the read is a plain `memcpy(buf, g_avbUserData.vbmeta_img_addr + offset, size)` and sets `*num_read = size`.

## 4. g_avbUserData globals (set by avb_ops_init)
```
0xFFFFFFFFE00643D8 = img_addr         (v166)
0xFFFFFFFFE00643E0 = vbmeta_img_addr  (v167)
0xFFFFFFFFE0064404 = img_size         (v38)
0xFFFFFFFFE0064408 = vbmeta_img_size  (v39)
```
Also 0xE00643D0 (img_name), 0xE00643E8, 0xE00643F0, 0xE0064400, 0xE006440C, 0xE0064410, 0xE0064418.
U-Boot passes addr/len via SMC ("from uboot smc...addr:0x%x len:0x%x").

## 5. AvbOps struct (libavb avb_ops.h) — pointer layout
```
+0x00 user_data
+0x08 ab_ops
+0x10 cert_ops
+0x18 read_from_partition
+0x20 get_preloaded_partition
+0x28 write_to_partition
+0x30 validate_vbmeta_public_key
+0x38 read_rollback_index
+0x40 write_rollback_index
+0x48 read_is_device_unlocked
+0x50 get_unique_guid_for_partition
+0x58 get_size_of_partition
+0x60 read_persistent_value
+0x68 write_persistent_value
+0x70 validate_public_key_for_partition
```

## 6. AvbSlotVerifyResult (libavb avb_slot_verify.h)
```
0 OK, 1 ERROR_OOM, 2 ERROR_IO, 3 ERROR_VERIFICATION, 4 ERROR_ROLLBACK_INDEX,
5 ERROR_PUBLIC_KEY_REJECTED, 6 ERROR_INVALID_METADATA, 7 ERROR_UNSUPPORTED_VERSION,
8 ERROR_INVALID_ARGUMENT
```

## Action items derived from this
1. `0x713f8` = load_and_verify_vbmeta; its result mapping is 0/1/2/3/6/7 (there is no -11 here).
2. Storage read = memcpy from `[0xE00643E0]+offset`, `*num_read=size`; set globals
   `[0xE00643E0]=vbmeta VA`, `[0xE0064408]=0x100000` instead of hardcoding in patch_read.
3. Locate where `-11` (`mov x0,#-0xb` at our 0x3f2f8) originates — it is in a DIFFERENT
   function (likely the trusty IPC / avb-service layer, not load_and_verify_vbmeta).


## 7. Crypto flow (avb_vbmeta_image.c + avb_rsa.c + crypto/sha256_impl.c)

`avb_vbmeta_image_verify(data, len, &pk, &pk_len)` (our 0x6ed70):
1. `len >= sizeof(header)` (256), magic == "AVB0".
2. `avb_vbmeta_image_header_to_host_byte_order` (big-endian -> host).
3. version check: `required_libavb_version_major != AVB_VERSION_MAJOR` OR
   `minor > AVB_VERSION_MINOR` -> **UNSUPPORTED_VERSION (3)**.
4. block sizes multiple of 64; header+auth+aux <= len.
5. hash within auth block; sig within auth block; pubkey within aux block.
6. algorithm == NONE -> **OK_NOT_SIGNED (1)**.
7. `hash_size == avb_get_algorithm_hash_size(algo)` (SHA256_RSA4096 -> 32).
8. `header_block = data; auth_block = data+256; aux_block = auth+auth_size;`
9. **computed_hash = SHA256(header_block(256) || auxiliary_block(aux_size))**  <- hash covers header + aux, NOT auth.
10. `image_verify_rsa(h, auth_block, aux_block, computed_hash)`.

`avb_rsa_verify(algorithm, key, key_len, sig, sig_len, hash, hash_len)`:
1. `iavb_parse_key_data(key)` -> modulus + rr (Montgomery R^2 mod n).
2. sig_len == key_len (512 for RSA4096); hash_len == 32.
3. `padding = PKCS1.5 prefix` (SHA256_RSA4096 = 0x30 0x31 0x30 0x0d 0x06 0x09 0x60 0x86 0x48 0x01 0x65 0x03 0x04 0x02 0x01 0x05 0x00 0x04 0x20, then 0xff filler to total 512).
4. `modpowF4(parsed_key, sig)` = `sig^65537 mod n` (Montgomery, exponent 0x10001).
5. result must == `padding || hash`.

So the full verify = SHA256(header||aux) then RSA-4096 PKCS#1-v1.5 verify with e=65537.
Our CE device implements exactly this and already returns 0 for the stock vbmeta.

## 8. Header field byte order (avb_vbmeta_image.h)
All `AvbVBMetaImageHeader` fields are **network byte order (big-endian)**; the
parser byteswaps via `avb_vbmeta_image_header_to_host_byte_order()` before use.
Offsets: magic[0], major[4], minor[8], auth_size[0xc], aux_size[0x14],
algorithm_type[0x1c], hash_offset[0x20], hash_size[0x28], signature_offset[0x30],
signature_size[0x38], public_key_offset[0x40], public_key_size[0x48],
public_key_metadata_offset[0x50], public_key_metadata_size[0x58],
descriptors_offset[0x60], descriptors_size[0x68], rollback_index[0x70], flags[0x78].
