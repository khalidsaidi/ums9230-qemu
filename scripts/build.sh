#!/bin/sh
# Clone QEMU (pinned), integrate ums9230.c, and build qemu-system-aarch64 (aarch64 only).
set -e
cd "$(dirname "$0")/.."
QEMU_DIR="${QEMU_DIR:-qemu}"
# QEMU revision this machine was developed against.
# (Newer QEMU removed ARMCPU.start_secure_el1, which ums9230.c relies on.)
QEMU_PIN="05f8e4662ad3976d64d6dfa2fdfa0ac6d28cbaa2"

if [ ! -d "$QEMU_DIR" ]; then
  git clone --depth 1 https://gitlab.com/qemu-project/qemu.git "$QEMU_DIR"
fi
git -C "$QEMU_DIR" fetch --depth 1 origin "$QEMU_PIN" 2>/dev/null || git -C "$QEMU_DIR" fetch origin "$QEMU_PIN" 2>/dev/null || true
git -C "$QEMU_DIR" checkout -q "$QEMU_PIN" 2>/dev/null || echo "warning: could not pin QEMU to $QEMU_PIN"

cp ums9230.c "$QEMU_DIR/hw/arm/ums9230.c"

python3 - <<'EOF'
import os
root = os.environ.get('QEMU_DIR', 'qemu')

meson_path = os.path.join(root, 'hw/arm/meson.build')
s = open(meson_path).read()
line = "arm_common_ss.add(when: 'CONFIG_UMS9230', if_true: files('ums9230.c'))\n"
if "CONFIG_UMS9230" not in s:
    lines = s.split('\n')
    lines.insert(2, line.rstrip('\n'))
    open(meson_path, 'w').write('\n'.join(lines))

kconfig_path = os.path.join(root, 'hw/arm/Kconfig')
s = open(kconfig_path).read()
if "config UMS9230" not in s:
    s += "\nconfig UMS9230\n    bool\n    default y\n    select PL011\n    select ARM_GICV3\n"
    open(kconfig_path, 'w').write(s)
print("ums9230 registered in meson.build + Kconfig")
EOF

mkdir -p "$QEMU_DIR/build"
cd "$QEMU_DIR/build"
../configure --target-list=aarch64-softmmu --without-default-features \
  --disable-tools --disable-docs
ninja qemu-system-aarch64
echo "built: $QEMU_DIR/build/qemu-system-aarch64"
