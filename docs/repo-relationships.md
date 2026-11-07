# Repo ↔ Work Relationship Tables

## 1. Global scope → repo (the full ums9230 boot + verified-boot + TEE stack)

| # | Stage / layer | What it owns | Repo |
|---|---|---|---|
| 1 | EL3 firmware | TrustZone split, PSCI, MMU init | arm-trusted-firmware |
| 2 | Bootloader | load+verify vbmeta, boot LK; canonical AvbOps | u-boot (`common/avb_verify.c`) |
| 3 | LK kernel | heap, pmm, vmm, MMU, page tables | lk, trusty_lk, trusty_lk_common |
| 4 | TEE OS | Trusty TEE + the avb glue (`vbmeta_img_addr`/`img_addr`) | trusty (SPRD fork = closed, not clonable) |
| 5 | Verified-boot verifier | avb_slot_verify, descriptors, RSA-4096, SHA-256 | libavb |
| 6 | Crypto backend | SHA-256 / RSA | external_boringssl, libavb/crypto |
| 7 | Device tree | SoC DTB | external_dtc |
| 8 | Android consumer | fs_mgr / dm-verity / AVB mount | system_core |
| 9 | Recovery | recovery-mode AVB path | bootable_recovery |
| 10 | Security policy | SELinux on top of verified boot | system_sepolicy, external_selinux |
| 11 | A/B update | rollback-index + slot verify consumer | system_update_engine |
| 12 | TEE-backed HALs | keymaster / gatekeeper / DRM | hardware_interfaces, optee_client |
| 13 | TEE reference | working TEE-on-QEMU (qemu_v8 target) | optee_os, optee_build |
| 14 | Emulator | machine model, TCG, devices | qemu |

## 2. AvbOps struct → payload table (+ u-boot reference)

`AvbOps` layout is fixed by `libavb/avb_ops.h`. Payload base = `0xffffffffe03548c8`
(read_is_device_unlocked = 0x6f354 sits at +0x48 = 0xffffffffe0354910).

| Off | Field | Payload addr | Payload value | u-boot reference impl |
|---|---|---|---|---|
| 0x00 | user_data | 0x...48c8 | ? | `ops_data` |
| 0x08 | ab_ops | 0x...48d0 | 0xffffffffe060d000 | NULL |
| 0x10 | cert_ops | 0x...48d8 | ? | NULL |
| 0x18 | read_from_partition | 0x...48e0 | 0xae0d0 (data — NOT code) | `avb_blk_byte_io` (block dev by name) |
| 0x20 | get_preloaded_partition | 0x...48e8 | 0x91550 | `get_preloaded_partition` |
| 0x28 | write_to_partition | 0x...48f0 | 0xae140 | `avb_blk_byte_io` |
| 0x30 | validate_vbmeta_public_key | 0x...48f8 | 0x8dff8 (data) | root-key digest compare |
| 0x38 | read_rollback_index | 0x...4900 | 0x37cf58 (`udf #0`) | `return 0 + OK` (no-TEE) |
| 0x40 | write_rollback_index | 0x...4908 | 0x37cf98 (`udf #0`) | `no-op + OK` (no-TEE) |
| 0x48 | read_is_device_unlocked | 0x...4910 | 0x6f354 (real) | `*out = true (unlocked) + OK` |
| 0x50 | get_unique_guid | 0x...4918 | 0x92360 | `get_partition` uuid |
| 0x58 | get_size_of_partition | 0x...4920 | 0xb5598 | — |

**Key finding:** the payload's ops table is only *partially* populated. The three
"real" SPRD paths are: `read_is_device_unlocked` (0x6f354, reads the global
`vb_unlock_status`) and a separate preloaded-buffer read path (the `0x200000`
src = `vbmeta_img_addr` global), NOT u-boot's block-device read. `read_rollback_index`
and `write_rollback_index` are `udf #0` placeholders; u-boot shows they should just
be `return 0 + OK`. The "read_from_partition = 0xae0d0 (data)" inconsistency means the
payload does NOT use a stock AvbOps table for reads — it uses SPRD globals
(`vbmeta_img_addr`, `img_addr`), which is the closed Unisoc glue.

## 3. Struct divergence: upstream lk vs payload (SPRD fork)

| Field | upstream lk `pmm_arena_t` | payload (from disasm) |
|---|---|---|
| node | 0x00 | 0x00 |
| name | 0x10 | (absent) |
| flags | 0x18 | 0x18 |
| priority | 0x1c | (absent) |
| base | 0x20 | 0x20 |
| kvaddr | 0x28 | **size @0x28** |
| size | 0x30 | **free_count @0x30** |
| free_count | 0x38 | **page_array @0x38** |
| reserved_count | 0x40 | (absent) |
| page_array | 0x48 | (absent here) |
| free_list | 0x50 | (absent) |

`vm_page_t` = 0x18 bytes, flags byte at +0x10 (bit0 = NONFREE) — matches payload.

The SPRD fork dropped `kvaddr`, `priority`, `reserved_count` and reordered the rest.
This is why upstream `pmm.c` alone couldn't be pasted onto the payload offsets.

## 4. Payload disassembled functions → source symbol

| Payload addr | Function | Source repo + symbol |
|---|---|---|
| 0x780dc | malloc | lk `kernel/lib/heap/*` (SPRD fork: free-list@0x58, used-list@0x68) |
| 0x73e04 | page_alloc | lk `common/lib/heap/page_alloc.c` |
| 0x73b20 | pmm_alloc_kpages | lk `kernel/vm/pmm.c` `pmm_alloc_kpages` |
| 0x74980 | vmm_alloc_physical | lk `kernel/vm/vmm.c` |
| 0x3aac | arch_mmu_map | lk `arch/arm64/mmu.c` |
| 0x3930 | vmm_find_region | lk `kernel/vm/vmm.c` |
| 0x745f0 | paddr_to_kvaddr | lk `kernel/vm/vm.c` |
| 0x6e2e0 | avb_memcpy | libavb `avb_sysdeps.h` `avb_memcpy` |
| 0x6b288 | SHA-256 update | libavb `crypto/sha256_impl.c` |
| 0x6ed70 | avb_slot_verify | libavb `avb_slot_verify.c` |
| 0x6f354 | read_is_device_unlocked | u-boot `common/avb_verify.c` (SPRD: reads global) |
| 0x713f8 | process_vboot_verify_smc | SPRD trusty (closed) |
