# SL8541E / SC9832E 启动链全解析

> **对象**：展讯 SL8541E / SC9832E 平台（vp19、DW99、AI3、M9U、DW100 等同族手表）。
> **依据**：BROM / splloader / sml / trustos / U-Boot 五件套实机固件全量逆向（反汇编 + 伪 C + 字节级校验），2026-10。
> **内容**：正常启动链（BROM→SPL→sml→trustos→U-Boot→Kernel）、两条 dloader 之路（临时 FDL / 固化 SPRD4）、三层安全校验与三部分绕过、usblog 注入、uboot_log 落盘、DHTB 与 SPRD Boot 镜像格式。

---

## 目录

1. 总览与地址映射
2. 正常启动链逐级解析
3. 启动交接件（CENV / bl_aux_params / logbuffer / 内核跳转）
4. 镜像格式：DHTB 与 SPRD 容器
5. 展讯 Boot 镜像格式（ANDROID! + SPRD 头）
6. 两条 dloader 之路
7. kick 协议与 SPRD4 完整链路
8. BSL 协议与收包状态机
9. 三层安全校验与三部分绕过
10. usblog 注入实现
11. uboot_log 落盘实现与局限
12. 附录：地址速查 / 日志对照 / 工具清单 / 未解之谜

---

## 1. 总览与地址映射

### 1.1 全景图

```
                     ┌──────────────────────────────┐
                     │        上电 / Reset           │
                     └──────────────┬───────────────┘
                                    ▼
      ┌──────────────────────────────────────────────────────────────┐
      │ BROM（已 dump：0x100000 起 0x12000B，287 函数全反编译）          │
      │  · 采样启动源 → 读 SPL 头(0x5000) → 校验 DHTB/摘要 → 跳 0x5200  │
      │  · BSL 保底下载（fdl1 由此进入）；★与 kick 零关系              │
      └──────────────────────────────┬───────────────────────────────┘
                                     ▼ 0x5200
      ┌──────────────────────────────────────────────────────────────┐
      │ SPL / splloader（SRAM 0x5000 起，DHTB 封装）                   │
      │  · EL 分派 / Cache / BSS / 时钟 / DDR 训练 / 调压              │
      │  · GPT 解析 → 加载 sml / trustos / uboot                      │
      │  · 写启动参数块 CENV@0x82000000（260=cboot / 258=download）    │
      │  · BLR 0x94000000 → sml                                      │
      └──────────────────────────────┬───────────────────────────────┘
                                     ▼
      ┌──────────────────────────────────────────────────────────────┐
      │ sml（ATF BL31 @0x94000000，EL3 安全世界，常驻）                 │
      │  · GIC / PSCI / SMC 总机；按序放行 BL32/BL33                   │
      └──────────────────────────────┬───────────────────────────────┘
                                     ▼
      ┌──────────────────────────────────────────────────────────────┐
      │ trustos（LK + Trusty TEE @0x94020000，EL1S，常驻）             │
      │  · AVB/vbmeta 校验、RPMB、Keymaster/Gatekeeper、HUK/eFuse、    │
      │    内存隔离、modem 防火墙                                     │
      └──────────────────────────────┬───────────────────────────────┘
                                     ▼
      ┌──────────────────────────────────────────────────────────────┐
      │ U-Boot（@0x9F000000，双角色：cboot / dloader）                 │
      │  · 正常：logo → vboot → 组参数 → 跳内核 0x80080000             │
      │  · 下载：SPRD4（被 kick）或 download 角色 → BSL dloader        │
      └──────────────────────────────┬───────────────────────────────┘
                                     ▼
                          Linux Kernel 入口 0x80080000
```

### 1.2 关键地址映射

| 阶段 | 镜像加载地址 | payload 入口 | 格式 | 备注 |
|---|---|---|---|---|
| SPL | 0x5000（SRAM） | **0x5200** | DHTB | 前 0x200 为 DHTB 头 |
| sml | 0x93FFFE00 | **0x94000000** | DHTB | BL31 |
| trustos | 0x9401FE00 | **0x94020000** | DHTB | BL32（Trusty） |
| U-Boot | 0x9EFFFE00 | **0x9F000000** | DHTB | BL33 |
| 内核 | 0x80000000 | **0x80080000** | ANDROID!(+SPRD 头) | 跳转实锤于 U-Boot `sub_9F017324` 尾部 |

**通用规律**：DHTB 镜像在内存里的“头”永远位于 payload − 0x200。

### 1.3 三个级间“约定件”

| 约定件 | 位置 | 生产方 | 消费方 | 内容 |
|---|---|---|---|---|
| **CENV 块** | 0x82000000 | SPL（`sub_555C`） | U-Boot（`sub_9F004DD8`） | "CENV" 魔数 + 角色（260/258）+ 内存表 |
| **bl_aux_params 表** | sml 内部（0x9400D0D8 / 0x9400D130） | sml | sml 自己 | BL32/BL33 入口登记 |
| **logbuffer** | 0x92400000 | U-Boot 控制台 | uboot_log 落盘 | 本次启动日志缓冲 |

---

## 2. 正常启动链逐级解析

### 2.1 BROM（片内掩膜 ROM，已 dump）

- **镜像**：`BootROM_sc9832e_0x100000_0x111FFF.bin`，**73728 B（0x12000）**，dump 范围 **0x100000 ~ 0x111FFF**，md5 `02071b7f498aa6c0f199c452fc816680`；伪 C **287 函数**（0 失败），入口 `brom_entry@0x100000`，主函数 `brom_main@0x10E730`。
- **身份**：固化在芯片内部的掩膜 ROM，不属于任何可刷分区。**“代码不可见”的旧说法作废**。
- **`brom_main`（104 B）**：`MEMORY[0x402E0004] |= 0x10` → 基础初始化 → `sub_10DFA4()` 判启动源（`==1` 走 `sub_10E5BC`，否则 `sub_10E52C`）→ `sub_10E0AC()` 取模式号 → **查表跳转** `(*(void(**)(void))(MEMORY[0x13C8] + 8*v0))()`。
- **SPL 加载与校验（`sub_101210`）**：
  1. `v4 = 20480`（**0x5000**），读 SPL 头 0x80 字节到 0x5000（`sub_10111C(a1,0,0x80,20480)`，两路重试）；
  2. 校验 `*(u32*)0x5000 == 0x42544844`（**“DHTB”**）且 `*(u32*)0x5030`（**[0x30] 本体长度**）`<= 0xFFFF`；
  3. `sub_101000(0x5008,0x20)` + `sub_10E798(0x5200,len,buf)` + `sub_10FB08(buf,0x5008,32)`：**对 0x5200 起的 SPL body 算 32 字节摘要，与头内 0x5008 处比对**（完整性校验，无 RSA 公钥参与）；
  4. 通过后跳 **0x5200**。
- **能力边界**：只会“收数据 + 搬运 + 校验 + 跳转”，**不会写分区**。
- **对外通道**：BSL 保底下载（`fdl fdl1 0x5000` 即此通道）。
- **★与 kick 完全无关（代码级）**：伪 C 中 `kick` / `pctool` / `calibrat` / `u2s` / `USB SERIAL` / `dloader` / `CENV` / `82000000` / `BSL` **全部 0 命中**（详见 7.4）。

### 2.2 SPL / splloader（SRAM 0x5000 起）

**入口 `start_0@0x5200` 的七件事**：

1. **EL 分派**：读 CurrentEL 走 EL3/EL2/EL1 分支（EL3 设 VBAR_EL3、CPTR_EL3=0、CNTFRQ_EL0=0x1800000；EL2 设 CPTR_EL2=0x33FF；EL1 设 CPACR_EL1=0x300000），临时栈 SP=0x3000。
2. **基础设施**：Cache 遍历清除/失效（`sub_A154`）、IC IALLUIS（`sub_A1E4`）、TLBI（`sub_A1F0`）、清 BSS（`sub_5208`，0xEFE0~0xF218）。
3. **平台初始化**（`sub_5888`）：时钟/PLL、PINMUX、调压（`vddcpu`=1100、`vddcore`=900）、切频、eMMC/SD PHY、**DDR 训练**（`sub_82D8`，日志 `DDR init start`/`DDR init OK`，失败打 `error:-3~-6` 并停机）。
4. **GPT 解析**：`sub_B58C` 校验 `EFI PART`（0x5452415020494645）、`sub_B600` 找分区、`sub_A330` 读数据。
5. **加载三镜像**：sml→0x93FFFE00、trustos→0x9401FE00、uboot 头→0x9EFFFE00（读 uboot 先读头 0x200，长度 = `*(hdr+48)+1024`）。
6. **写 CENV 启动参数块**（`sub_555C`）：

   ```c
   MEM[0x82000000] = 0x43454E56;   // "CENV"（作为 u32 大端读）
   MEM[0x82000004] = 260;          // 260=正常(cboot) / 258=下载(download)
   MEM[0x82000008] = 0;
   ```

   配套 `sub_81EC` 写内存表（`[+8]=0x40000000`、`[+0x20]=1`、`[+0x24]=0x40000000`）并同步 0x300001B4/B8。
7. **交棒**：`MOV W0,#0x104; BL sub_555C; MOV X0,#0x94000000; BLR X0` → **跳 sml**（不直接跳 U-Boot）。

> ⚠️ `260` 是 SPL 里的**硬编码立即数**；二进制里搜不到 "CENV" 字符串（用 MOV/MOVK 立即数拼成）。

### 2.3 sml（ATF BL31，EL3）

- **身份**：ARM Trusted Firmware BL31（字符串实锤 `plat/sprd/sharkle/pm.c`、`gicv2_driver_init`、`sprd_bl31_setup.c`、`bl31/bl31_main.c`）。
- **职责**：
  1. 建立 EL3 环境（向量表/栈）、GIC 初始化；
  2. PSCI 电源管理、`sprd_cpu_standby`；
  3. **登记交棒表**：BL32（trustos 0x94020000）与 BL33（U-Boot 0x9F000000）写入 bl_aux_params；
  4. 通过 `bl31_plat_get_next_image_ep_info` 取下一个镜像入口，用 **ERET** 依次放行 trustos → U-Boot；
  5. **常驻**：系统运行期间作为 EL3 总机转发 SMC。
- **注意**：U-Boot 对 sml/trustos 的地址**零代码引用**——只通过 SMC 与之通话，不回跳。

### 2.4 trustos（LK + Trusty TEE，EL1S）

- **身份**：完整 Trusty TEE（`lk/trusty/lib/uthread/uthread.c`、`app/keymaster/*`、17 个 `com.android.trusty.*` / `com.sprd.trusty.*` 服务）。
- **职责**（“真操作系统”）：
  - **校验**：AVB/vbmeta（`Loading vbmeta struct from partition '%s'`）、RSA 验签、RPMB 读 key；
  - **内存**：安全/非安全内存映射（`sm_decode_ns_memory_attr`、`ns_mem.c`）；
  - **信任根**：HUK 烧写/派生（`sprd_wr_huk`、`efuse_huk_program`）、SoC ID（`sprd_socid_get`）、hwkey 服务；
  - **通信**：与 U-Boot/内核的 SMC（`have got sip smc all from uboot###`、`from uboot smc...`）+ virtio/TIPC；
  - **虚拟化**：`trusty_virtio.c`、vqueue；
  - **熔断/驱动/加解密**：eFuse、AES/RSA/ECC 引擎全套、tamanager；
  - **modem 管理**：`sprd_recreate_cp_modem`、`sprd_set_modem_firewall`。
- **启动**：`start@0x94020000` 清表、建页表（MAIR_EL1=0xFF0400、TCR_EL1=0x2B523351A）、多核 bootstrap2。

### 2.5 U-Boot（BL33）

- **入口**：`start@0x9F000000` → EL 分派 → MIDR → 早期 init → **自身重定位**（清 gd、拷 `start..0x9F06E268`、修 R_AARCH64_RELATIVE、DC CIVAC + IC IALLU）→ C 世界。
- **读 CENV 定角色**（`sub_9F004DD8`/`sub_9F004D5C`）：
  - 校验 `MEM[0x82000000]==0x43454E56`，复制 48B 到 0x9F083258；
  - 258 → `bootcmd="download"`；260 → `bootcmd="cboot"`（否则 `"Chipram magic wrong"`）。
- **双角色字符串**："two roles:dloader and cboot"。
- **正常启动（cboot）**：模式检查链 → 显示 logo → 提取 vboot key（`sprd_get_vboot_key()`，读 sechdr）→ RPMB imgversion → 组装参数 → **跳内核**。
- **下载/工具能力**：SPRD4 dloader、fastboot、pctool（get/set_recovery_message、get_rootflag、setrma/getlcs/getsocid）、`common_raw_write` 分区写、`write_sparse_img` 稀疏写。

### 2.6 Linux Kernel

- U-Boot 收尾函数 `sub_9F017324`（由 `sub_9F0182B8` 的 boot 流程调用）：
  1. `init_log_buffer` / `init_log_partition_hdr`（uboot_log 落盘，见第 11 节）；
  2. `flush_log_buffer`；
  3. USB 电源切换（`sub_9F031BB0`）；
  4. MMU 收尾（`sub_9F0012BC(0x80000000,0xA0000000)`、`(0x180000000,0x1A0000000)`）等；
  5. **`MEMORY[0x80080000](a1,0,0,0)`** —— 跳内核入口 **0x80080000**（x0 传参数指针），然后死循环不再返回。
- cmdline 来源：arm64 上 **boot.img 头部的 cmdline 字段不生效**，全部来自 DTB 的 `chosen/bootargs`（`androidboot.super_partition=super androidboot.dynamic_partitions=1 firmware_class.path=/vendor/firmware` 等）。

---

## 3. 启动交接件（CENV / bl_aux_params / logbuffer / 内核跳转）

### 3.1 CENV 块（SPL → U-Boot 的启动角色约定）

| 偏移 | 内容 |
|---|---|
| +0x00 | 0x43454E56（按大端读作 ASCII "CENV"） |
| +0x04 | **260**（正常 cboot）/ **258**（下载 download） |
| +0x08 | 0 |
| +0x1C | 附加参数（258 时由 `sub_52D8` 填） |
| +0x20 | 1 |
| +0x24 | 0x40000000（内存布局） |

### 3.2 U-Boot 模式体系（cboot 的检查链与跳转表）

`bootcmd="cboot"`（无参数）→ `sub_9F004A14`（命令表第 7 项）→ 依次跑**检查链 `off_9F068C30[0..8]`**，第一个返回非零者的返回值 = 模式号：

| idx | 函数 | 检测内容 | 可能返回 |
|---|---|---|---|
| [0] | `sub_9F004B68` | 电池电量（低电走充电/等待） | 0 |
| [1] | `sub_9F004BB8` | 记录的启动模式（`sub_9F004B00` 读寄存器） | 0 |
| [2] | `sub_9F004B4C` | **pctool 检测（kick 路口，u2s）** | 16 / 18 / 19 |
| [3] | `sub_9F004BD4` | misc recovery message（`sub_9F01C0A4`） | 3 |
| [4] | `sub_9F004BF4` | 记录模式位掩码 0x1527C7 | 模式 |
| [5] | `sub_9F004C5C` | （未展开） | — |
| [6] | `sub_9F004C9C` | （未展开） | — |
| [7] | `sub_9F004CBC` | （未展开） | — |
| [8] | `sub_9F004D3C` | power-on source（`sub_9F023C80`） | 2（normal） |

**模式跳转表 `sub_9F002970(v10)`**：

| 模式 | 处理器 | 语义 |
|---|---|---|
| 2 | `sub_9F0184D4` | normal |
| 3 | `sub_9F018568` | recovery |
| 4 | `sub_9F0186DC` | fastboot |
| 5 | `sub_9F018850` | alarm |
| 6 | `sub_9F0187CC` | charge |
| 7 | `sub_9F018810` | engtest |
| 16 | `sub_9F018500` | calibration（kickto 非 2/21 时兜底） |
| 17 | `sub_9F018884` | factorytest |
| **18** | **`sub_9F0187B8`** | **SPRD4 / dl_diag（kickto 2）** |
| 19 | `sub_9F018534` | autotest（kickto 21） |
| 20 / 22 | `sub_9F0185D8` / `sub_9F0188B8` | 其它 / sprdisk |

带参形式（`cboot normal` 等）走 `sub_9F004960` 字符串匹配：`normal`=2、`recovery`=3、`fastboot`=4、`charge`=6、`sprdisk`=22、`sysdump`=0。

---

## 4. 镜像格式一：DHTB（固件分区统一封装）

### 4.1 结构

```
偏移            内容
0x000           "DHTB" 魔数（44 48 54 42），版本 u32@4 = 1
0x008~0x02C     保留（多为 0）
0x030           payload 长度 size（u32 LE）★不可改
0x034~0x1FF     其余头字段（多为 0）
0x200           payload 起点（= 加载目标 − 0x200）
0x200+size      sechdr 安全头（验签信息）
0x200+size+0x60 cert 证书段（实例 uboot：sechdr 0x760F0 → cert 0x76150）
尾部            sechdr+cert 区（实测约 0x294~0x2B4 字节，到有效尾为止）
```

### 4.2 实测量值（vp19 系列）

| 镜像 | 文件长度 | [0x30] | sechdr = [0x30]+0x200 | 有效数据尾 |
|---|---|---|---|---|
| splloader | 0x40000（256KB） | 0x91E0 | 0x93E0 | 0x9694 |
| sml | 0x100000（1MB） | 0xC090 | 0xC290 | 0xC524 |
| trustos | 0x3E0494 | 0x3E0000 | 0x3E0200 | 0x3E0494 |
| U-Boot | 0x763A4（484260B） | 0x75EF0 | 0x760F0 | 0x763A4 |

**内存规律**：DHTB 头永远位于 payload − 0x200（uboot：头 0x9EFFFE00 / payload 0x9F000000；sml/trustos 同理）。U-Boot 的 vboot 读取 `sechdr_offset = [0x30] + 0x200`（日志实锤 "sechdr_offset is 0x760f0"）。

### 4.3 修改规则（血泪教训）

- **[0x30] 不可改**：一改就触发 vboot 错位 → “亮屏后 3.3 秒无限重启”（复位循环）。
- **文件不可加长**：追加字节同样触发复位循环。
- **一切补丁必须等长原地替换**（单字/同长改写），本系列所有补丁遵守此规则。

---

## 5. 镜像格式二：展讯 Boot 镜像（ANDROID! + SPRD 头）

`boot` 分区镜像 = 标准 Android boot image（header v0）**+ 展讯私有 DTB 包裹头**（SPRD 头，2048 字节）。

### 5.1 ANDROID! 头（2048B，字段实锤于打包脚本）

| 偏移 | 字段 | 值（DW99 实测） |
|---|---|---|
| 0 | magic | `ANDROID!` |
| 8 | kernel_size | 内核大小 |
| 12 | kernel_addr | **0x8000** |
| 16 | ramdisk_size | ramdisk 大小 |
| 20 | ramdisk_addr | **0x05400000** |
| 24 | second_size | 0 |
| 28 | second_addr | **0x00F00000** |
| 32 | tags_addr | **0x00000100** |
| 36 | page_size | **2048** |
| 40 | **dt_size（展锐特有）** | DTB 段大小（含 SPRD 头） |
| 44 | os_version/unk2 | **0x12000000**（Android 9.0.0 编码） |
| 48 | os_patch_level | 空 |

**布局**：`头(2048) → kernel 段（2048 对齐）→ ramdisk 段（2048 对齐）→ DTB 段`。

**DTB 段 = SPRD 头（2048B）+ 裸 DTB**；裸 DTB（魔数 `d0 0d fe ed`）会被打包器自动套 SPRD 头。

> arm64 注意：boot.img 头部的 cmdline 字段**不生效**（内核只取 DTB 的 chosen/bootargs）。

### 5.2 SPRD 头（2048B，DTB 包裹头）

```
偏移      内容（实测 hex）
0x00      53 50 52 44          "SPRD" 魔数
0x04      01 00 00 00          版本 =1
0x08      01 00 00 00          =1
0x0C      68 26 00 00          0x2668（= 9832，平台号）
0x10      01 00 00 00          =1
0x14      00 00 02 00          0x20000
0x18      00 08 00 00          0x800（= 2048）
0x1C      （裸 DTB 大小）        ★打包时按实际 DTB 长度写入（u32 LE）
0x20+     其余为 0
```

- **打包两条路径**（“已包裹直用” / “裸 DTB 自动套头”）经往返验证**逐字节一致**，且与 magiskboot 解析结果一致。
- `0x1C` 写入值 = 裸 DTB 字节数；DTB 段整体 = 2048 + 裸 DTB。

### 5.3 其它相关容器

- **PAC**：刷机包（XML + 各镜像 + fdl1/fdl2 路径与地址）；`pac_magic != ~0x50005` 即非法。
- **sparse image**：U-Boot / fdl2 原生支持（magic 0xED26FF3A；chunk 0xCAC1/2/3/4）。

---

## 6. 两条 dloader 之路（临时 vs 固化）

**核心认知**：本平台有**两套下载器**——“临时的”和“固化的”。两者**同源代码族**（`u-boot15/common/dloader`），协议同为 **BSL**，差别只在“谁在跑、从哪儿来”。

### 6.1 临时 dloader：BROM + FDL1 → FDL2

**工作方式**：PC 每次刷机时**现场**把下载器代码推进设备 RAM 执行；掉电即消失。

```
[PC: sfd_tool]                                [设备]
    │ 1. BROM 阶段：send fdl1（≈37KB）→ fdl1_base（8541e = 0x5000，SRAM）
    │───────────────────────────────────────▶ BROM 收下并驻留
    │ 2. BSL_CMD_EXEC_DATA(0x04) → "Execute FDL1"
    │───────────────────────────────────────▶ BROM 跳入 fdl1
    │ 3. 握手：CHECK_BAUD / CONNECT → "FDL1 connected"
    │◀───────────────────────────────────────▶
    │ 4. 可选 CHANGE_BAUD(0x09) / KEEP_CHARGE(0x13)
    │ 5. FDL1 阶段：send fdl2（≈0.5MB）→ fdl2_base（DDR）
    │───────────────────────────────────────▶ fdl1 收下 fdl2
    │ 6. EXEC_DATA → fdl1 跳入 fdl2
    │ 7. "Device is in FDL2 stage now, flash pac"
    │───────────────────────────────────────▶ fdl2 = 完整刷机引擎
```

- **fdl1**（远小于 40KB）：BROM 的“补完”——接管通信、变速、保充电、接收 fdl2 并执行；
- **fdl2**（约 0.5MB）：完整刷机协议（分区读写/擦除/repack/NV/稀疏镜像……）；
- **地址**：fdl1 由命令指定（8541e 为 0x5000）；fdl2 地址由 **PAC 内 XML 的 addr 字段**给出；
- **为什么叫“临时”**：fdl1/fdl2 全在 RAM，**每次刷机都要重新上传**；`sfd_tool` 日志体现为 `Execute FDL1` / `Execute FDL2`。

### 6.2 固化 dloader：U-Boot 内置（SPRD4 / download 角色）

**工作方式**：下载器代码**常驻 eMMC 的 uboot 分区**（U-Boot 本体的一部分），无需上传。

两个入口：

1. **角色入口**：CENV=258 时 `bootcmd="download"`（SPL 决定“本次开机就是下载”）；
2. **kick 入口**（重点）：正常启动过程中，检查链 [2] 在 u2s 通道上收到 **kick 帧** → 当场切换为 **SPRD4（AutoD）** 下载态。

进入后的特征：

- 注册 7 项 BSL 命令表（0/1/2/3/4/9/19），向 PC 自报 `"SPRD4:AutoD"`；
- PC 端看到 SPRD4 后 **"Skipping FDL send in SPRD4 mode"**——不传 fdl1/fdl2，直接 `exec` 进 `do_download`；
- `do_download`（`sub_9F004774`）注册 **19 个命令**：`1 / 2 / 3 / 16 / 17 / 18 / 10 / 11 / 5 / 23 / 13 / 25 / 26 / 127 / 32 / 33 / 34 / 37 / 12`，随后进入收包循环。

### 6.3 两套对比

| 维度 | 临时 dloader（BROM+FDL） | 固化 dloader（U-Boot/SPRD4） |
|---|---|---|
| 宿主 | BROM → fdl1 → fdl2 | U-Boot（cboot 检查链捕获 kick，或 download 角色） |
| 代码来源 | PC 现场上传（fdl1 + fdl2） | eMMC 固件（uboot.img 内置组件） |
| 存活 | 掉电即失 | 常驻 |
| 触发 | 停在 BROM；`fdl` 推送 + EXEC | kick 帧 / CENV=258 / 工具选择 |
| 工具日志 | `Execute FDL1` / `Execute FDL2` | `Skipping FDL send in SPRD4 mode` |
| 地址 | fdl1=0x5000；fdl2=PAC 指定 | 就地执行（已在 RAM） |
| 共同点 | **同源代码（common/dloader）+ 同一 BSL 命令体系** | 同左 |

---

## 7. kick 协议与 SPRD4 完整链路

### 7.1 kick 帧（10 字节）

PC（`sfd_tool ChangeMode`）通过 **u2s**（U-Boot 的 USB 串口，设备端名 "USB SERIAL"）发送：

```
字节:  0    1  2  3  4  5   6   7     8      9
      7E   00 00 00 00 08  00  FE   82     7E        ← kickto 2（dl_diag）
      │                            │    │      │
     帧头                    命令类(0xFE) 模式=0x80|N  帧尾
```

- `--kickto N`：第 8 字节 = `0x80 + N`；
- `--kick`：第 8 字节 = `0x81`；
- 设备端解析（`sub_9F01A34C`，0xFE 分支）：

```c
v = (a1[8] & 0x3F) + ((a1[1]<<8 | a1[2] | a1[3]<<16) << 8);
```

对 kick 帧（a1[1..3]=0）→ **v = N**，日志打印 `checked command from pc , and return value = 2`。

### 7.2 模式路由（`sub_9F01A840` = pctool_mode_detect）

| v18 | 处理 | 返回 | 结果 |
|---|---|---|---|
| 0 | 失败（`caliberate failed`） | -1 | 忽略，继续正常启动 |
| **2** | **`sub_9F031BB0`（切 USB 电源）** | **18** | **★ SPRD4** |
| 21 | 填 `"autotest=1"` | 19 | autotest |
| 23 | eFuse 特殊分支（再收 14/16 字节） | 6 / 1 | 熔断操作 |
| 其它 | 填 `"calibration=%d,..."` | 16 | calibration 模式 |

> 即：`--kickto 1` → calibration；**`--kickto 2` → SPRD4（dl_diag）**；≥64 的取值被 `&0x3F` 截回低 6 位。

### 7.3 完整链路（一图）

```
PC(sfd_tool)                                 U-Boot（启动检查阶段）
  │ 0. 打开 u2s（DTR=1）                        │
  │ 1. 发 10 字节 kick 帧                       │
  ├───────────────────────────────────────────▶ sub_9F01A580 读入 10B@0x9F1BE278
  │                                             │   （前置：USB 校准等待——"USB SERIAL CONFIGED" /
  │                                             │     "USB SERIAL PORT OPENED"，超时 3000/2000）
  │                                             ▼ sub_9F01A34C 解析 → v=2
  │                                             ▼ sub_9F01A840 → return 18
  │                                             ▼ v10[18]=sub_9F0187B8
  │                                             ▼ sub_9F01C420（SPRD4）
  │ 2. 等 0x7E 后回 "SPRD4:AutoD"                │
  │◀─────────────────────────────────────────── sub_9F01C2C4
  │ 3. 识别 SPRD4："Skipping FDL send in SPRD4 mode"
  │ 4. 发 exec（BSL）                           │
  ├───────────────────────────────────────────▶ sub_9F01C330
  │                                              第 1 次：ACK + 再报 SPRD4
  │                                              第 2 次：sub_9F004774 = do_download
  │ 5. 进入 FDL 收包循环                         │
  │◀──────────────────────────────────────────── FDL_PacketDoIdle + 19 命令
```

---

### 7.4 BROM 与 kick 的完全无关性（已 dump 验证）

BROM 已 dump 并全量反编译（287 函数，0 失败），伪 C 中 u2s / pctool 相关关键词**全部 0 命中**：

| `kick` | `pctool` | `calibrat` | `u2s` | `USB SERIAL` | `dloader` | `BSL` | `CENV` | `82000000` |
|---|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

- BROM 侧只有：启动源采样 → 读 SPL 头 → “DHTB”+长度+摘要校验 → 跳 0x5200，**不含任何 USB/串口协议栈**；
- kick 的收帧（`sub_9F01A580`）、解析（`sub_9F01A34C`）、模式路由（`sub_9F01A840`）**全部在 U-Boot 内**，且只有启动进 U-Boot 后才存在；
- 结论：**kick 与 BROM 零关系**，此前基于间接证据的推断已被 BROM 代码级证实。

---

## 8. BSL 协议与收包状态机

- **帧界**：`0x7E` 起始/结束；`0x7D` 转义（后一字节 XOR 0x20）；
- **校验**：CRC16（多项式 0x1021，`sub_9F013EFC`）或累加和（`sub_9F013F5C`），依 `MEM[0x9F1C3094]` 选择；**校验失败 → 回错误码 139 + 死循环**；
- **收包**：`sub_9F01432C`（=`FDL_PacketDoIdle`，源码路径 `common/dloader/packet.c`）逐字节状态机（0 找头 → 1/2 收数据 → 3 完成），挂队列 `MEM[0x9F0896E0]`；
- **取包**：`sub_9F014660`；**分发**：`sub_9F01C254`（按 `__rev16` 大端命令号查 `MEM[0x9F1C3088]` 链表）；
- **回包**：`sub_9F0140A4 / 0142A0`（专用分配 + 发送路径）。

---

## 9. 三层安全校验与三部分绕过

### 9.1 三层校验分别在哪里

| 层 | 校验什么 | 执行者 | 失败表现 |
|---|---|---|---|
| ① secure boot | SPL 对后续镜像（uboot 等）的完整性/签名校验 | SPL | 校验序列失败 → 死循环 |
| ② bootloader lock | 解锁标志（miscdata）→ 决定 fastboot 刷写与验证行为 | U-Boot（`sub_9F04AD20`） | `Flashing Lock Flag is locked. Please unlock it first!` |
| ③ AVB/vbmeta | 分区级验证（vbmeta/启动镜像哈希链） | trustos | 校验不通过 → 拒绝/回退 |

### 9.2 三部分绕过（等长原地补丁）

**① splloader no-secure-boot**

```
file 0x54C0:  a0 04 00 94  (BL 0x6740 校验序列)
         →    47 00 00 14  (B  0x55DC 跳过)
```

语义：uboot 载入 0x9F000000 后跳过整段校验（校验代码仍存在，不执行）。

**② U-Boot unlock-bootloader**

```
file 0x4AF64: 60 00 00 34  (CBZ W0)         →  NOP (1F 20 03 D5)
file 0x4AF68: 3f 98 08 b9  (STR WZR,[X1,#.]) →  NOP
file 0x4AF6C: 03 00 00 14  (B)              →  NOP
```

语义：`sub_9F04AD20` 读 miscdata 的 LOCK 校验被直通 → `[0x9F1BB898]` 恒 =1（UNLOCK）→ 打印 `"LOCK FLAG IS : UNLOCK"` 并跳过验证。

**③ trustos no-avb**

```
file 0x24960: e0 03 14 2a  (MOV W0, W20)  →  00 00 80 52  (MOV W0, #0)
file 0x25CF8: e0 03 14 2a  (MOV W0, W20)  →  00 00 80 52  (MOV W0, #0)
```

语义：两个校验函数序言强制返回 0（=通过），AVB 恒过。

### 9.3 逐设备偏移表

| 设备 | splloader | U-Boot | trustos |
|---|---|---|---|
| vp19 | 0x54C0 | 0x4AF64 | 0x24960 / 0x25CF8 |
| ai3 | 0x54C0 | 0x4AFBC | 同上 |
| m9u | 0x54C0 | 0x4B294 | 同上 |
| dw99 | —（未扫） | 0x4B134（YC 已解锁） | — |
| dw100 | —（未扫） | 0x4AE44（YC 已解锁） | — |

（另有可选**横幅替换**：`WARNNING: LOCK FLAG IS...` / `INFO: LOCK FLAG IS...` 字符串槽位，等长写入自定义文案。）

### 9.4 补丁工具链

- **unlock-auto**：按字节特征自动定位三类补丁点（spl 的 `a0040094` + 前后缀、uboot 的 `3f9808b9` 五指令链、trustos 的 `bf030091` + `e003142a` ×2）；
- **8541E-Uboot-Patcher**：一键三合一（去保护 + usblog + 横幅），附 Web 版（纯前端，产物与 Python 逐字节一致）。

---

## 10. usblog 注入实现

**目标**：把 U-Boot 控制台输出**实时**从 u2s（USB 串口）送出，用于没有可用 UART 的场景。

### 10.1 结构

```
┌─ puts 入口（1 字补丁）────────────────────────────────────────────┐
│  原第一条指令 → B 跳进"死区"注入块                                  │
└──────────────────────────────────────────────────────────────────┘
┌─ 死区（选定"永不被调用"的函数体：fastboot flashing 子命令处理器）──────┐
│  gate 变量 / 触发桩 / 日志函数 / 钩子 / 发送泵调用                    │
└──────────────────────────────────────────────────────────────────┘
┌─ 触发桩（1 字补丁 @ "USB SERIAL PORT OPENED" 的 printf 调用点）──────┐
│  置 gate=1（此后所有 puts 都旁路一份到 USB）                         │
└──────────────────────────────────────────────────────────────────┘
```

**日志函数逻辑**（概念）：

```c
log_hook(s):
    if (!gate) return;          // USB 通道未就绪前不动作
    gate = 0;                   // 防重入（发送期间再进入直接跳过）
    len = strlen(s);
    send_via_u2s(s, len);       // 走 pctool 发送泵（分片 ≤1 个 max packet）
    gate = 1;
```

### 10.2 各设备锚点（示例）

| 设备 | puts 入口 | 触发桩 | 注入区（死区） |
|---|---|---|---|
| vp19 | 0xE798 | 0x1A768 | 0x1BC34 起 |
| ai3 | 0xE790 | 0x1A770 | 0x1BC58..0x1BE40 |
| dw99 | 0xE770 | 0x1A740 | 0x1BC28..0x1BE10 |
| dw100 | 0xE770 | 0x1A740 | 同 dw99 |
| m9u | 0xE770 | 0x1A740 | 0x1BC28..0x1BECC |

（**usblog-auto** 用 23 锚点自动定位：TRIG ← "USB SERIAL PORT OPENED" 字符串引用 + 双原子断言消歧；随后刚性偏移 RET1=TRIG−4、FORCE_PORT=TRIG−0x48、PUMP_CALL=TRIG+0x188、REPLY=TRIG+0x154；再推 PRINTF / STOCK_PUMP / FLAG_TX / PORTFLAG / 死区。）

### 10.3 PC 侧读取（关键坑）

- reader 只认 **bcdDevice 0x2416**；
- 必须发 **`SET_CONTROL_LINE_STATE` wValue=1（仅 DTR）** 打开端口——**发 wValue=3 反而会关闭端口**（历史连环坑的真凶）；
- claim_interface 必须真成功；bulk EP 0x85 持续轮询（100ms），收到即 fsync；
- **发送泵（`sub_9F02D0F0`）无超时等待 TX-complete** → 主机端必须一直读；日志发送按**≤1 max packet 分片**（最终版修复，根治阻塞）。

### 10.4 成果与验证

- 真机完整实时日志 **2608B / 67 行**（从 `USB SERIAL PORT OPENED` 到 `init_log_partition_hdr(): init log partition header sucess!`）；
- 与设备 **uboot_log 分区槽位逐字节一致**；
- 发布镜像（vp19 0.0.1）：`uboot-0.0.1.img` 484260B，md5 `aa780e3b...`，基于解锁基线 `a03efc26...` 构建；
- 所有补丁产物经反汇编级验证（全部分支目标检查 + 0 字节越界审计）后才可刷。

---

## 11. uboot_log 落盘实现与局限

### 11.1 分区与格式（实锤）

- **分区**：`uboot_log`（mmcblk0p11，**4MB**）。
- **两个独立日志区**（按启动角色）：
  - 角色 **260（cboot）** → 分区偏移 **0x0**；
  - 角色 **258（download）** → 分区偏移 **0x200000**。
- **每区结构**：

```
+0x000  512B 头：
     +0x00  magic = 0xABCD（43981）
     +0x04  0x200（数据区起点）
     +0x08  1
     +0x0C  槽数 = 6
     +0x10  角色
     +0x14  环形写指针
     +0x18  6 条记录 ×12B：{u32 偏移, u32 长度, u32 槽大小 = 0x40000}
+0x200   数据槽 0（256KB）
+0x40200 数据槽 1
+0x80200 数据槽 2
+0xC0200 数据槽 3
+0x100200 数据槽 4
+0x140200 数据槽 5（环形，写满回绕覆盖）
```

### 11.2 落盘流程（代码级）

```
每次启动的 U-Boot 收尾（sub_9F017324，跳内核前）：
  init_log_buffer()          // 清状态（0x9F083810 区 112B）
  init_log_partition_hdr()   // sub_9F00CFB8：
                             //   读头 → 老设备推进环形指针 / 新设备重建头
                             //   擦除目标槽（256KB）
                             //   打印 "init_log_partition_hdr(): init log partition header sucess!"
  flush_log_buffer()         // sub_9F00D234：
                             //   把 RAM 日志缓冲（logbuffer@0x92400000）
                             //   按增量写入该槽 + 回写头（长度生效）
  ... vddusb 切换 / MMU 收尾 ...
  MEMORY[0x80080000](...)    // 跳内核
```

日志内容 = **U-Boot 本次启动的全部控制台输出**（含显示初始化、vboot、RPMB、USB 校准等），末尾就是那句 `init_log_partition_hdr(): ... sucess!`。

### 11.3 局限（重点）

- **只记录“走完启动”的日志**：落盘发生在**跳内核之前的最后一步**。设备**卡死 / 崩溃 / 复位 / 停在下载模式**时该步未执行 → **零记录**。
  → 因此 uboot_log **不能用于排查“不开机”**，只能回看“曾经成功启动过”的那些次的日志。
- 只含 **U-Boot 阶段**日志（不含 SPL / trustos / 内核）。
- 环形 6 槽：新刷掉旧（每区只留最近 6 次启动）。
- 与 usblog 互补：usblog 是“实时流”（只要能进 U-Boot 就能看），uboot_log 是“遗体黑匣子”（只对成功的启动有效）。

---

## 12. 附录

### 12.1 关键地址速查

| 项 | 地址/值 |
|---|---|
| BROM（已 dump） | 0x100000~0x111FFF（73728B；entry 0x100000，main 0x10E730） |
| SPL 入口 | 0x5200 |
| sml / trustos / U-Boot payload | 0x94000000 / 0x94020000 / 0x9F000000 |
| CENV 参数块 | 0x82000000 |
| 日志缓冲 logbuffer | 0x92400000 |
| 内核入口 | 0x80080000 |
| pctool 检测 | `sub_9F01A840`；收帧 `sub_9F01A580`；解析 `sub_9F01A34C` |
| kick 路由 | `sub_9F004B4C`（检查链[2]）→ `return 18` |
| SPRD4 | `sub_9F01C420`（注册）/ `sub_9F01C2C4`（自报）/ `sub_9F01C330`（exec） |
| do_download | `sub_9F004774` |
| 日志落盘 | `sub_9F00CFB8`（init）/ `sub_9F00D234`（flush） |
| 分区写 | `sub_9F013604`（common_raw_write）/ `sub_9F016A70`（sparse） |

### 12.2 标志性日志对照

| 阶段 | 日志样例 |
|---|---|
| SPL | `DDR init start` / `DDR init OK` |
| U-Boot(pctool) | `USB SERIAL CONFIGED` / `USB SERIAL PORT OPENED` / `usb calibrate port open timeout…` |
| U-Boot(kick) | `checked command from pc , and return value = 2` / `caliberate_mode: 2` |
| U-Boot(SPRD4) | `SPRD4:AutoD` |
| U-Boot(解锁) | `LOCK FLAG IS : UNLOCK` / `Flashing Lock Flag is locked…` |
| U-Boot(日志) | `init_log_partition_hdr(): init log partition header sucess!` |
| trustos | `have got sip smc all from uboot###` / `Loading vbmeta struct from partition '%s'` |

### 12.3 工具清单

sfd_tool（刷机/kick）、usb_reader.py / read_com_log.py（usblog 读取）、usblog-auto（锚点自动定位+注入）、unlock-auto（补丁点自动定位）、8541E-Uboot-Patcher（三合一，含 Web 版）、parse_uboot_log.py（uboot_log 解析）、mkbootimg.py + sprd_header.bin（boot.img 打包）。

### 12.4 未解之谜

1. `u2s accessed via keypad` 路径（sfd_tool sendloop 注释暗示的“按键直进 u2s”）；
2. SPRD4 命令表中 16/17/18/23/25/26/32/33/34/37/127 等命令的完整语义；
3. `sub_9F031BB0` 操作 `0x20E00000` bit4 与 vddusb 的硬件细节；
4. 检查链 [5][6][7] 三个检测器的完整语义；
5. BROM 中 `sub_10DFA4` / `sub_10E0AC` 的启动源编号与 `MEMORY[0x13C8]` 跳转表的完整映射。

---

*（本文档基于 vp19 / DW99 系列实机固件逆向整理，2026-10-05。所有偏移为文件偏移；VA = 文件偏移 + 基址。）*
