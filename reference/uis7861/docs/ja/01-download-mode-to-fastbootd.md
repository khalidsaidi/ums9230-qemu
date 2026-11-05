# 01. Download ModeからfastbootdへのExploit

## Download Mode (BROM) について

Unisoc/SpreadtrumのSoCは、電源投入時に特定の条件(ボタン組み合わせ、または
正常起動の失敗)でBROM(Boot ROM、マスクROM)の**Download mode**に入ります。
BROMはチップに焼き込まれたROMのため、u-boot以降がどれだけ壊れてもDownload mode自体は
基本的に生き続けます。これが本リポジトリで想定している「最終的な復旧手段」です。

Download modeはPC側から`spd_dump`のようなツールでUSB経由で接続し、FDL1→FDL2という
2段階のローダーを順にロードして初めて、パーティションの読み書き等ができるようになります。

```
PC --USB--> BROM (Download mode) --FDL1--> FDL1 --FDL2--> FDL2 (read_part/write_part等が使える状態)
```

## CVE-2022-38694: BROM署名検証バイパス

正規のBROMは、ロードするFDL1/FDL2に対して署名検証を行います。署名されていない
(改変された)FDL1/FDL2をロードしようとすると拒否されます。

[CVE-2022-38694](https://nvd.nist.gov/vuln/detail/CVE-2022-38694)は、BROMの
`exec_addr`(任意アドレスへのジャンプ実行)コマンドを使うことで、この署名検証を
**毎回**バイパスできる脆弱性です。[TomKing062/CVE-2022-38694_unlock_bootloader](https://github.com/TomKing062/CVE-2022-38694_unlock_bootloader)
に実装されたPoCがあり、`custom_exec_no_verify_65015f08.bin`という小さなシェルコードを
`exec_addr`経由で実行させることで、以降ロードするFDL1/FDL2の署名検証を無効化します。

実際のコマンド列(`unlock_autopatch_9230.bat`より):

```
spd_dump exec_addr 0x65015f08 fdl fdl1-dl.bin 0x65000800 fdl fdl2-dl.bin 0x9efffe00 exec ...
```

- `exec_addr 0x65015f08` — BROM内の特定アドレスにジャンプし、署名検証をパッチする
  シェルコード(`custom_exec_no_verify_65015f08.bin`)を実行
- `fdl fdl1-dl.bin 0x65000800` — 署名検証が無効化された状態で、**未署名の**FDL1を
  そのアドレスにロード
- `fdl fdl2-dl.bin 0x9efffe00` — 同様に未署名のFDL2をロード

これは1回だけ有効になるパッチではなく、**BROMとの接続セッションのたびに毎回
実行し直す**必要があります(BROM自体のコードは書き換えられておらず、RAM上の
実行時パッチのため電源を切ると消える)。

## 使用ツール

- `spd_dump`(libusb版ビルド) — 通常配布されているSPRD純正ドライバ前提のビルドとは別に、
  `TomKing062/spreadtrum_flash`の`stable_*`リリースに含まれる、libusb + Zadig/WinUSB
  ドライバで動作するビルドを使う必要があります。純正ドライバ前提のビルド(`Channel9.dll`
  経由)は、WinUSBドライバ環境では接続できませんでした。
- 未署名FDL一式(`fdl1-dl.bin`, `fdl2-dl.bin`, `custom_exec_no_verify_65015f08.bin`) —
  `CVE-2022-38694_unlock_bootloader`リポジトリより。

## fastbootdへの入り方

fastbootd(fastboot in userspace、動的パーティション操作用)へは、Android標準の
BCB(Boot Control Block、`misc`パーティション)経由の方法で入れます。`misc`は
署名検証の対象外の非保護パーティションなので、`spd_dump`で素直に書き込めます。

`scripts/Enter-Fastbootd.ps1`は、`misc`パーティションに適切なBCBコマンド
(`boot-fastboot`相当)を書き込んでからリブートすることで、fastbootdへ誘導します。

```powershell
.\Enter-Fastbootd.ps1
```

fastbootdに入った後は、通常の`fastboot`コマンド(`fastboot devices`,
`fastboot flash`, `fastboot delete-logical-partition`等)がそのまま使えます。

## 復旧経路としてのDownload mode

u-boot自体を改変した結果、起動が完全に停止する(画面に何も出ない)状態になっても、
本体の電源ボタン等でDownload modeへの強制突入を試みれば、大抵は復旧できます
(実際にこのプロジェクトでも、u-bootの改変を誤って何度も起動不能状態に陥りましたが、
すべてDownload mode経由で復旧できました)。**改造作業を始める前に、必ずstockの
`uboot_a`/`uboot_b`/`super`等をDownload mode経由で一度バックアップしておくことを
強く推奨します**(`Dump-Boot.ps1`、および`Flash-Raw.ps1`での`super`丸ごと読み出し)。
