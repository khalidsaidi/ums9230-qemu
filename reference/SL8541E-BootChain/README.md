# SL8541E / SC9832E 启动链研究

展锐（Unisoc / Spreadtrum）SL8541E / SC9832E 平台手表（vp19、DW99、AI3、M9U、DW100 等同族设备）的启动链逆向成果。

五件套全部做过：BROM、splloader（SPL）、sml（ATF BL31）、trustos（LK + Trusty TEE）、U-Boot。每件都给出现场镜像与逐函数伪 C，另有一份完整文档把链路串起来。

完整文档：**[SL8541E-SC9832E-boot-chain.md](./SL8541E-SC9832E-boot-chain.md)**（670 行）

## 仓库结构

```
SL8541E-BootChain/
├── SL8541E-SC9832E-boot-chain.md     启动链全解析（主文档）
├── 原厂启动链-vp19/                  原厂（带锁 + AVB）五件套
│   ├── BROM/       BootROM dump + 伪 C（287 函数）
│   ├── SPLLoader/  splloader.bin + 伪 C（176 函数）
│   ├── SML/        sml.bin + 伪 C（276 函数）
│   ├── TrustOS/    trustos.bin + 伪 C（715 函数）
│   └── U-Boot/     uboot.bin + 伪 C（1646 函数）
└── 开发启动链-vp19/                  去保护版（no secure boot / no AVB / 解锁）
```

## 地址映射

| 阶段 | 文件内偏移 0 | 运行地址 | 入口 | 说明 |
| --- | --- | --- | --- | --- |
| BROM | 0x100000 | ROM 内 | 0x100000 | 掩膜 ROM，dump 范围 0x100000~0x111FFF（73728 B） |
| splloader | 0x0 | 0x5000 | 0x5200 | DHTB 封装，BROM 只校验头 0x80 字节 |
| sml | 0x0 | 0x93FFFE00 | 0x94000000 | ATF BL31，EL3 |
| trustos | 0x0 | 0x9401FE00 | 0x94020000 | LK + Trusty TEE，EL1S |
| U-Boot | 0x0 | 0x9EFFFE00 | 0x9F000000 | payload 在 0x9F000000 |

规律：DHTB 头放在 payload 前 0x200 处，即 `头部地址 = payload 地址 - 0x200`。

## 已确认的关键结论

- 启动链：BROM → splloader → sml → trustos → U-Boot → kernel。SPL 末尾 `BLR 0x94000000` 跳 sml，sml 不引用 U-Boot 地址，由 trustos 转交（trustos 内有 7 处 0x9F000000 引用）。
- 启动参数块：SPL 往 0x82000000 写 CENV 头与模式号，260 = 正常启动（bootcmd=cboot），258 = 下载模式（bootcmd=download）。U-Boot 侧 `sub_9F004DD8` 校验 magic 后据模式设 bootcmd。
- kick 协议（PC 发 10 字节 7E 帧让设备进 SPRD4 / 校准）全链在 U-Boot 内：接收 `sub_9F01A580`、解析 `sub_9F01A34C`、路由 `sub_9F01A840`。BROM 内 kick / pctool / u2s / USB SERIAL 全部 0 命中，两者完全无关。
- BROM 负责 SPL 加载：读 0x80 字节头到 0x5000，校验 `DHTB` 与 [0x30] 上限，对 body 做 32 字节摘要比对，最后跳 0x5200。
- 三层安全校验：BROM 校验 SPL，SPL 无校验（直读），trustos 做 AVB/vbmeta 校验，U-Boot 侧另有 secure_verify_partition / vboot_secure_process_flow。三部分绕过方法见主文档第 9 章。
- usblog：钩 puts 入口，用 `reply_to_pctool` 把控制台输出推到 u2s 串口，得到 U-Boot 运行期实时日志。
- uboot_log 分区（mmcblk0p11）：4 MB，头部 magic 加若干 256 KB 槽，只有在完整成功启动后才写。卡在任何一步都是零记录，不能用于排查不开机。
- 原厂 U-Boot 里大量「出错就 while(1) 原地死转」与「判不出启动模式就关机」的写法，是自编译 U-Boot 上机卡死的常见原因，清单见主文档附录。

## 关于伪 C

伪 C 由 IDA 9.4 无头模式（`idat -A -S`）对实机镜像全量反编译得到，函数体与符号地址可直接与二进制对照。变量名为 v1、a1 形式，未做重命名，保留原始结构便于逐条核对反汇编。

## 免责声明

本仓库内容仅用于设备互操作性研究、教学与自家设备维护。仓库内附带的厂商固件镜像（BROM、splloader、sml、trustos、U-Boot）版权归原作者所有，仅作为逆向分析对象随仓库提供。请勿用于商业用途或他人设备。

## 相关仓库

- [8541E-Uboot-Patcher](https://github.com/Dunoguang/8541E-Uboot-Patcher)：三件套去保护 + usblog 注入 + 横幅替换（含网页版）
- [uboot-usblog](https://github.com/Dunoguang/uboot-usblog)：早期二进制注入版 usblog 方案与主机端 reader
- [Watch-GKI](https://github.com/Dunoguang/Watch-GKI)：SL8541E 平台 4.4 内核
