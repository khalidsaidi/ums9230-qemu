# 03. 脆弱性を突いたイメージの書き込み

## 症状: 署名済みFDL2では改変イメージが書き込めない

純正・署名済みの`fdl1-sign.bin`/`fdl2-sign.bin`を使って`write_part`で
`uboot_a`/`uboot_b`に**改変したイメージ**を書き込むと、最後のチャンクでACKが
返らず`unexpected response`のようなエラーで失敗し、書き込み済みサイズが
対象サイズより少ない状態(末尾が欠落)で止まります。stock(無改変)イメージは
毎回クリーンに書き込めます。

## 原因: FDL2レベルでの書き込みデータ署名検証

`spd_dump`(spreadtrum_flash)のソース`common.c`の`load_partition()`関数に、
以下のような記述があります:

```c
if (!ret) {
    if (n == n64) ERR_EXIT("signature verification of \"%s\" failed or timeout reached\n", name);
    else ERR_EXIT("timeout reached\n");
}
```

最終チャンクでACKが来ない場合、ツール作者自身が「署名検証失敗」と明記しています。
つまり**署名済みFDL2は`write_part`時に書き込みデータそのものの署名を検証しており、
改変された`uboot_a`/`uboot_b`の書き込みを(部分的に)拒否します**。これは
u-boot自身のランタイム検証(root_of_trust, AVB。[02](02-uboot-patching.md)参照)とは
全く別の、**FDL2レベルでの書き込み時保護**です。

## 解決策: 未署名FDLによる書き込み

[01](01-download-mode-to-fastbootd.md)で説明したCVE-2022-38694の`exec_addr`
バイパスを、FDL2のロード時にも使います。これにより、署名検証を一切行わない
**未署名の`fdl1-dl.bin`/`fdl2-dl.bin`**をロードして使うことができ、
`write_part`時のデータ署名検証自体を回避できます(readbackでバイト単位一致を
確認済み)。

```
spd_dump exec_addr 0x65015f08 fdl fdl1-dl.bin 0x65000800 fdl fdl2-dl.bin 0x9efffe00 exec write_part <partition> <offset> <size> <file> reset
```

## `Flash-Raw.ps1 -Unsigned`

`scripts/Flash-Raw.ps1`にこの仕組みを`-Unsigned`スイッチとして実装しています。

```powershell
# uboot_a/uboot_bに改変イメージを書き込む(署名検証バイパス必須)
.\Flash-Raw.ps1 -Unsigned -Files @(
    "uboot_a=.\uboot_a_patched.bin",
    "uboot_b=.\uboot_b_patched.bin"
)
```

- `-Unsigned`を付けない場合は署名済み`fdl1-sign.bin`/`fdl2-sign.bin`経由の
  通常の書き込みになります。`vbmeta_*`/`misc`等の非保護パーティションには
  `-Unsigned`は不要ですが、付けても害はありません。
- `uboot_a`/`uboot_b`のような保護対象パーティションへ改変イメージを書く場合は
  `-Unsigned`が必須です。
- 実行には通常の`spd_dump.exe`ではなく、libusb版の`spd_dump_dl.exe`
  (`TomKing062/spreadtrum_flash`の`stable_*`リリース)が必要です。

## 応用: GSIのインストール

上記の仕組みを使えば、`system_a`をGeneric System Image (GSI)に入れ替えることも
できます。手順の考え方は以下の通りです。

### `super`パーティションの空き容量確保

Android Virtual A/Bでは、`super`パーティション内にOTA更新時のスナップショット用
`*-cow`予約領域が確保されています。stock状態だとこの予約のせいで`super`内に
ほとんど空きが無く、GSIの`system.img`(stockより大きいことが多い)を書き込む
だけの領域が確保できません。使っていない`*-cow`を0バイトに縮小して空きを作ります:

```powershell
fastboot resize-logical-partition system_a-cow 0
fastboot resize-logical-partition vendor_a-cow 0
fastboot resize-logical-partition product_a-cow 0
# 等
```

これは`super`の中身を作り変える操作なので、事前に`super.img`全体をバックアップ
(`Flash-Raw.ps1`で丸ごと読み書き可能)しておくことを強く推奨します。

`product_a`/`system_ext_a`/`vendor_a`はfstabで`required` mountに指定されており、
削除すると起動不能になることを実機検証で確認済みです。GSI導入で置き換えるのは
`system_a`のみにとどめてください。

### 子vbmetaの無効化 + system_aの入れ替え

1. トップレベルvbmeta**以外**の子vbmeta(system/vendor/product/system_ext/odm)の
   flagsを`0x00000003`に書き換えてから`fastboot flash`([02](02-uboot-patching.md)の
   AVBイメージフォーマット参照)
2. `system_a`を`delete-logical-partition`で削除し、GSIの`system.img`サイズ
   ぴったりで`create-logical-partition` → `flash`
3. `fastboot -w`で`userdata`を初期化
4. `reboot`

### fastbootのraw sparse自動分割バグへの対処

`max-download-size`を超えるrawファイルを送る際、一部バージョンのfastbootは
自動でsparse分割を試みますが、"Invalid sparse file format at header magic" /
"Error reading sparse file"で失敗する不具合があります。回避策として、事前に
`ConvertTo-SparseImage.ps1`で正規のsparseイメージ(圧縮はせず、ファイル全体を
1個のrawチャンクとしてsparse形式でラップするだけの最小実装)に変換してから
送信します。
