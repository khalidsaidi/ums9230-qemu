#!/bin/sh
set -e
export PATH=/home/khali/.local/bin:$PATH
R=/home/khali/ums9230-qemu
cd "$R"
git init -b main
git config user.name khalidsaidi
git config user.email khalidsaidi@users.noreply.github.com
git add -A
git commit -m "ums9230-qemu: minimal Unisoc UMS9230/T606 trustos TEE machine

Boots the trustos payload and drives avb_vbmeta_image_verify to
demonstrate the vbmeta result (-11 rejected / 0 patched)."
gh repo create ums9230-qemu --public --source . --push --description "Minimal QEMU machine for the Unisoc UMS9230/T606 trustos TEE — boots trustos and shows the vbmeta -11 vs 0 result."
