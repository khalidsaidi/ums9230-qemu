# 02. u-bootバイナリの解析とパッチ

## 起動時の壁: 生バイナリ編集は検証で弾かれる

[01](01-download-mode-to-fastbootd.md)の方法で署名検証を回避して`uboot_a`/`uboot_b`に
書き込みができるようになっても、pristine(無改造)な`uboot_a.bin`を**直接バイト編集**
したファイルをそのまま書き込むと、変更内容に関わらず(実行されない未使用領域の
1バイト変更ですら)、画面に何も表示されず(バックライトも点かず)起動が完全に
停止します。stockイメージは毎回正常に起動するため、書き込み失敗ではなく、
u-boot本体が実行される**前段階**(SPL/FDL1)で、書き込まれた`uboot_a`/`uboot_b`の
内容を何らかの基準(チェックサム/ハッシュ)と照合し、一致しないと実行させない、
という**起動時の整合性検証**が存在すると考えられます。この検証ロジック自体は
SPL/FDL1側にあり、Download modeからは読み取り保護されているため(`spl_a.bin`/
`spl_b.bin`は常に0バイトとして読み出される)、直接解析はできません。

## 回避策: Patch-Post-Verification方式

[TomKing062/unisoc_chipram_signcheck_exploit](https://github.com/TomKing062/unisoc_chipram_signcheck_exploit)
由来の`magic64.exe`/`difftool.exe`を使います。

**仕組み**: 元のペイロードのバイト列を一切変更せず、ペイロードの直前に小さな
「ジャンプコード」を追加します。起動時、まずこのジャンプコードが実行され、
末尾に埋め込まれた**パッチテーブル**(アドレス+新しい値のペア)の内容をメモリに
自己書き換えしてから、本来のペイロードへジャンプします。つまり**静的な
ファイル内容(検証対象)は無改造のまま**で、**実行時の自己書き換えでパッチが
適用される**ため、起動時の整合性検証を通過できます。

### 手順

1. pristine(無改造)な`uboot_a.bin`をコピーし、当てたいパッチをバイト単位で
   直接書き込んだファイルを作る(`uboot_a_patched_src_XXX.bin`)
2. `difftool`でランタイムパッチテーブル入りのイメージを生成:
   ```bash
   ./difftool.exe uboot_a_patched_src_XXX.bin patched.bin 0x9F000000 uboot_final_XXX.bin
   ```
   (`patched.bin`は`magic64.exe`で無改造版から一度だけ生成した固定のフレームワーク)
3. 出力ファイルはパーティション容量(`0x300000`バイト)をわずかに超えることがあるので、
   先頭`0x300000`バイトに切り詰めてから書き込む(実質的な内容は先頭付近に収まるため
   安全)
4. `Flash-Raw.ps1 -Unsigned`で書き込む([03](03-unsigned-flashing.md)参照)

**以後のu-bootパッチはすべてこの方式で作成する必要があります。生バイナリを
直接編集したファイルをそのまま書き込んではいけません。**

## u-boot内の検証ロジック(Ghidra解析)

### 二層構造: Unisoc独自層 + 標準AVB

このデバイスは**Unisoc独自の検証層(`root_of_trust` / `sprd_verify_cert`)**と
**標準のGoogle AVB(`avb_slot_verify`)**の**2段構え**になっています。u-bootバイナリ内に
libavbのソース文字列が埋め込まれており、標準AVB実装そのものが含まれていることが
確認できます。Unisoc層はAVBより**手前**で動作し、Unisoc層を通過しない限り
標準AVBの検証結果にはたどり着けません。

- Unisoc層のゲート関数: `set_root_of_trust`
- 標準AVBのエントリポイント: `avb_slot_verify`(文字列
  `"Rebooting because of dm-verity corruption"`への唯一のXREFから特定)

呼び出しチェーン(通常起動ハンドラ内):
```
FUN_XXXX()   AVB検証結果を androidboot.vbmeta.pubkey=... 等のcmdlineに変換
FUN_XXXX()   verifiedbootstate に応じて "SKIP VERIFY" 等をログ表示
FUN_XXXX()   ← Unisoc独自層のroot_of_trustチェック本体(set_root_of_trust)
```

### パッチ1: root_of_trust バイパス

呼び出し元関数内、`set_root_of_trust(...)`の戻り値を見る`CBZ`命令を無条件分岐
`B`に変更し、戻り値に関わらず常に「成功」扱いにします。

```
元命令:   CBZ W0, #<target>   ; 0x340000xx
パッチ後: B #<target>          ; 0x14000xxx
```

CBZ/CBNZ/TBZ/TBNZをB(無条件分岐)に変えるだけなので、imm26を再計算して
`0x14000000 | imm26`にすればよく、パッチとしては最も単純な部類です。

### AVB検証内の2つの真の根本原因

root_of_trustバイパスだけでは効果がないケースがありました。`set_root_of_trust`が
内部で呼んでいる別関数の中に、AVB検証結果が非0の場合に**意図的に無限ループで
永久停止する安全装置**があったためです:

```c
undefined8 FUN_XXXX(undefined4 param_1, undefined4 param_2)
{
  int *piVar1 = (int *)FUN_YYYY(0x36, param_1, param_2);
  if (*piVar1 != 0) {
    /* ログ出力 */
    do { /* 意図的な無限ループ */ } while (true);
  }
  return 0;
}
```

disabled化したvbmetaの状態では、この判定結果が非0になり、この無限ループに
突入していました。root_of_trustバイパスだけでは、この関数自体が戻ってこないため、
戻り値を見るバイパス処理まで到達できていなかったのです。

さらに遡ると、この無限ループに入る根本原因は**`avb_slot_verify`内部の実装バグ**
でした。`load_and_verify_vbmeta`内の「`VERIFICATION_DISABLED`ビットが立っている場合」
専用の分岐(検証無効化vbmetaを処理する簡易パス)で、パーティションサイズ取得用の
OPS関数ポインタを**nullチェックせずに直接呼び出して**いました:

```c
iVar6 = (**(code **)(ops + 0x58))(ops, partition_name, &out_size);  // ← nullチェック無し
```

他のOPS関数ポインタ(オフセット `+0x18, 0x30, 0x38, 0x50, 0x60, 0x68`)はすべて
事前に`assert_fail: ops->xxx`形式でnullチェックされているのに、`+0x58`(おそらく
`get_size_of_partition`)だけそのチェックが抜けていました。このデバイスのAVB ops
実装では`+0x58`が未実装(不正な値)になっており、直接呼び出すと即クラッシュします。
これがベンダー実装側の抜け漏れであり、上記の判定結果が非0になる直接の原因でした。

### 特定方法: プリントマーカー方式によるバイナリサーチ

無限ループを仕込んで「ハングするか/シャットダウンするか」で二分探索する方法は、
一度クラッシュ修正を重ねると**すべてのテストが「ハング」で見分けがつかなくなる**
という問題があります(画面には一定の表示以降、新しい内容が一切描画されないため)。

そこで、**ループさせず、その地点を通過したら独自メッセージを画面表示してから
本来の処理をそのまま継続する**コードケイブパッチに切り替えました
(呼び出し前後でレジスタをスタックに退避・復元し、対象関数を実際に呼び出した上で
処理を続行する)。これにより「そこを通過したか」を、処理を止めずに確認できます。
この方式で無限ループの正確な位置を特定しました。

**注意点**: このパターンで既存の関数呼び出しをコードケイブ経由に差し替える場合、
呼び出し規約(AAPCS64)上の**caller-saved(一時)レジスタ X0-X17**をすべて
退避・復元する必要があります。特に、末尾呼び出し(tail call)の直前にチェックポイントを
挿入する場合は要注意です。tail callの直前では、呼び出し元がすでに次の関数への
引数(X0-X3等)をセットアップ済みであることが多く、チェックポイント内で呼ぶ
診断用print関数がこれらのレジスタを破壊すると、意図しない引数でカーネルへ
ジャンプすることになり、原因不明のクラッシュ/ハングを招きます(実際にこの問題で
不具合パッチを作ってしまった経験があります)。

## 最終的なパッチ内容(動作確認済み)

| # | 内容 | 種別 |
|---|---|---|
| 1 | root_of_trust bypass(CBZ→B) | 単純上書き |
| 2 | avb_slot_verifyの未検証OPS関数ポインタ呼び出しをスキップ | コードケイブ。呼び出し先で`*param_3(サイズ出力先)=0; return 0;`を実行してから復帰 |
| 3 | 意図的無限ループをバイパス(CBZ→B) | 単純上書き |

disabled化したvbmeta(`vbmeta_a`+子vbmeta、flags=`0x3`=
`VERIFICATION_DISABLED|HASHTREE_DISABLED`)の状態のまま、上記3パッチを適用して
通常起動(電源投入)したところ:

```
enter boot mode 2                          <- 正常な通常起動モード
set_root_of_trust succeeded.
enter mode normal, consume time: 4568ms    <- 完了、ループなし
```

その後カーネルへ正常にジャンプし、Android初期化フェーズまで到達することを
確認しました。

## vbmeta改変時の挙動まとめ

| 変更対象 | 症状 | 原因 |
|---|---|---|
| トップレベルvbmetaを単独で改変 | u-boot起動が停止 | Unisoc独自層(root_of_trust)がvbmeta自体の状態を検知して安全装置が働く。上記パッチで解決 |
| 子vbmeta(system/vendor/product/system_ext)のみ改変、トップレベルはstock | u-bootは通過するが遅延カーネルパニック(`Attempted to kill the init task!`) | トップレベルvbmetaのAVBチェーン記述子(子vbmetaのハッシュ)がstockのままだと不整合を検知してカーネル側でパニックする |

**結論**: トップレベルvbmetaと子vbmeta(system/vendor/product/system_ext)は
必ずセットでdisabled化する必要があります。

### AVBイメージフォーマット(flags書き換えの参考)

- 256バイトの固定長ヘッダ、マジック`"AVB0"`(先頭4バイト)
- フラグはヘッダオフセット120、**ビッグエンディアン**4バイト
  - `0x1` = `AVB_VBMETA_IMAGE_FLAGS_HASHTREE_DISABLED`
  - `0x2` = `AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED`
  - `0x3` = 両方無効化
- `fastboot --disable-verity --disable-verification`は、ダンプ済みイメージの
  パディング起因で`rewrite_vbmeta_buffer()`がfooterを見つけられず失敗することが
  あるため、上記flagsバイトを直接書き換える方式のほうが確実です。
