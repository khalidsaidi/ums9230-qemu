# UIS7861/UIS7863 (Unisoc UMS9230 / QOGIRL6) u-boot AVB Bypass

[English](README.md)

Android車載ディスプレイオーディオ(Unisoc UMS9230系, QOGIRL6プラットフォーム)向けに、
u-boot内のUnisoc独自セキュアブート層(`root_of_trust`)と標準Google AVB
(`avb_slot_verify`)の両方をバイパスし、任意の改変イメージ(GSI等)を起動できるようにする
ための調査記録・ツール集です。

## 対象デバイス

- SoC: Unisoc/Spreadtrum UMS9230 (QOGIRL6), UIS7861/UIS7863
- `ro.hardware`: `uis7861_6h10`
- ブートローダーは [CVE-2022-38694](https://nvd.nist.gov/vuln/detail/CVE-2022-38694) で
  事前にアンロック済み(BROM Download modeの署名検証を`exec_addr`/`loadexec`経由で
  バイパスする脆弱性)であることが前提です。

## 前提となる免責事項

- 本リポジトリの内容は**自己所有デバイスに対する正規の改造・セキュリティ調査**を目的としています。
- 記載の手順は対象デバイスのroot_of_trust/AVB検証を無効化するため、**保証は完全に失われ、
  デバイスがブリック(文鎮化)するリスクがあります**。実行は自己責任でお願いします。
- Download mode(BROM)はマスクROMで動作するため、u-boot以降がどれだけ壊れても
  基本的に復旧経路は残りますが、100%の保証はありません。

## 全体像: 2段階の壁

改変イメージを書き込んで実行できるようになるまでに、2つの独立した壁がありました。

1. **書き込み時の壁**(FDL2の署名検証) — 署名済みFDL2は`write_part`時に書き込みデータ
   自体の署名を検証しており、改変イメージの書き込みを拒否する。
   → [`docs/ja/01-download-mode-to-fastbootd.md`](docs/ja/01-download-mode-to-fastbootd.md) /
   [`docs/ja/03-unsigned-flashing.md`](docs/ja/03-unsigned-flashing.md)
2. **起動時の壁**(u-boot自身の整合性検証 + root_of_trust/AVB) — 署名検証を回避して
   書き込めても、u-bootのペイロードを直接バイト編集すると起動時の整合性チェックで
   弾かれる。さらにそれを回避しても、Unisoc独自のroot_of_trustと標準AVBの二重の
   検証が残っている。
   → [`docs/ja/02-uboot-patching.md`](docs/ja/02-uboot-patching.md)

## ドキュメント構成

| ドキュメント | 内容 |
|---|---|
| [01. Download ModeからfastbootdへのExploit](docs/ja/01-download-mode-to-fastbootd.md) | CVE-2022-38694を使ったBROM署名検証バイパス、Download mode操作、fastbootdへの入り方 |
| [02. u-bootバイナリの解析とパッチ](docs/ja/02-uboot-patching.md) | Ghidraでの解析手順、root_of_trust/AVBバイパスパッチの内容、Patch-Post-Verification手法 |
| [03. 脆弱性を突いたイメージの書き込み](docs/ja/03-unsigned-flashing.md) | 未署名FDL経由での`-Unsigned`書き込み、GSIインストール手順 |

英語版は [`docs/en/`](docs/en/) にあります。

## scripts/

このリポジトリの手順を自動化するPowerShellスクリプト一式です(スクリプト本体は英語)。
詳細な使い方は各docsを参照してください。

- `Flash-Raw.ps1` — Download modeから任意パーティションへ書き込み。`-Unsigned`で
  署名検証バイパス経路を使用可能。
- `Enter-Fastbootd.ps1` — `misc`パーティション(BCB)経由でfastbootdへ誘導。
- `Dump-Boot.ps1` — `spl_a`/`spl_b`/`uboot_a`/`uboot_b`を読み取り専用でダンプ。
- `Dump-Logs.ps1` — `uboot_log`/`sysdumpdb`パーティションを読み取り専用でダンプ
  (u-bootコンソールログ・カーネルクラッシュダンプの回収に使用)。
- `ConvertTo-SparseImage.ps1` — raw imgをAndroid sparse形式に変換(fastbootの
  raw分割バグ回避用)。

これらのスクリプトは以下のサードパーティツールに依存しますが、ライセンス上の理由から
本リポジトリには同梱していません。それぞれの配布元から入手してください。

- `spd_dump` (libusb版) — [TomKing062/spreadtrum_flash](https://github.com/TomKing062/spreadtrum_flash)
- `magic64.exe` / `difftool.exe` (Patch-Post-Verification手法) —
  [TomKing062/unisoc_chipram_signcheck_exploit](https://github.com/TomKing062/unisoc_chipram_signcheck_exploit)
- 未署名FDL / `custom_exec_no_verify_*.bin` —
  [TomKing062/CVE-2022-38694_unlock_bootloader](https://github.com/TomKing062/CVE-2022-38694_unlock_bootloader)

## .claude/

同じワークフローを再現したい方向けに、実際の調査で使用した
[Claude Code](https://claude.com/product/claude-code) のskill/agent定義も
[`.claude/`](.claude/README.md) に収録しています。

## Credits

- [TomKing062](https://github.com/TomKing062) — CVE-2022-38694のPoC実装、
  `spreadtrum_flash`、`unisoc_chipram_signcheck_exploit`。本調査全体の土台となっている。
- CVE-2022-38694自体の発見者・報告者(Unisoc BROM Download modeの署名検証バイパス脆弱性)。

## License

このリポジトリ内のオリジナルスクリプト・ドキュメントは [MIT License](LICENSE) の下で
公開します。上記サードパーティツールはそれぞれの元リポジトリのライセンスに従います。
