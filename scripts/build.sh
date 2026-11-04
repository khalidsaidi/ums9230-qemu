#!/bin/sh
# Clone QEMU (pinned), patch the ARM CPU for Secure-EL1 reset, integrate
# ums9230.c, and build qemu-system-aarch64 (aarch64 only).
set -e
cd "$(dirname "$0")/.."
QEMU_DIR="${QEMU_DIR:-qemu}"
# QEMU revision this machine was developed against.
QEMU_PIN="05f8e4662ad3976d64d6dfa2fdfa0ac6d28cbaa2"

if [ ! -d "$QEMU_DIR" ]; then
  git clone --depth 1 https://gitlab.com/qemu-project/qemu.git "$QEMU_DIR"
fi
git -C "$QEMU_DIR" fetch --depth 1 origin "$QEMU_PIN" 2>/dev/null || git -C "$QEMU_DIR" fetch origin "$QEMU_PIN" 2>/dev/null || true
git -C "$QEMU_DIR" checkout -q "$QEMU_PIN" 2>/dev/null || echo "warning: could not pin QEMU to $QEMU_PIN"

# register the machine source
cp ums9230.c "$QEMU_DIR/hw/arm/ums9230.c"

# patch QEMU + register the machine in the build
python3 - "$QEMU_DIR" <<'EOF'
import sys
root = sys.argv[1]

# 1) add the start_secure_el1 field to ARMCPU (cpu.h)
p = root + '/target/arm/cpu.h'
s = open(p).read()
old = '''    /* CPU has security extension */
    bool has_el3;
    /* CPU has PMU (Performance Monitor Unit) */'''
new = '''    /* CPU has security extension */
    bool has_el3;
    /* start at Secure EL1 instead of EL3 (for TEE blobs loaded at EL1) */
    bool start_secure_el1;
    /* CPU has PMU (Performance Monitor Unit) */'''
if "start_secure_el1" not in s:
    assert old in s, "cpu.h marker not found"
    s = s.replace(old, new, 1)
    open(p, 'w').write(s)

# 2) reset into Secure EL1 when start_secure_el1 is set (cpu.c)
p = root + '/target/arm/cpu.c'
s = open(p).read()
old = '''        /* Reset into the highest available EL */
        if (arm_feature(env, ARM_FEATURE_EL3)) {
            env->pstate = PSTATE_MODE_EL3h;
        } else if (arm_feature(env, ARM_FEATURE_EL2)) {
            env->pstate = PSTATE_MODE_EL2h;
        } else {
            env->pstate = PSTATE_MODE_EL1h;
        }'''
new = '''        /* Reset into the highest available EL */
        if (cpu->start_secure_el1 && arm_feature(env, ARM_FEATURE_EL3)) {
            env->pstate = PSTATE_MODE_EL1h;
            env->cp15.scr_el3 = 0x430; /* NS=0 secure, RW=1 aarch64 */
        } else if (arm_feature(env, ARM_FEATURE_EL3)) {
            env->pstate = PSTATE_MODE_EL3h;
        } else if (arm_feature(env, ARM_FEATURE_EL2)) {
            env->pstate = PSTATE_MODE_EL2h;
        } else {
            env->pstate = PSTATE_MODE_EL1h;
        }'''
if "start_secure_el1 && arm_feature" not in s:
    assert old in s, "cpu.c reset marker not found"
    s = s.replace(old, new, 1)
    open(p, 'w').write(s)

# 3) register the machine in the build
meson_path = root + '/hw/arm/meson.build'
s = open(meson_path).read()
line = "arm_common_ss.add(when: 'CONFIG_UMS9230', if_true: files('ums9230.c'))\n"
if "CONFIG_UMS9230" not in s:
    lines = s.split('\n')
    lines.insert(2, line.rstrip('\n'))
    open(meson_path, 'w').write('\n'.join(lines))

kconfig_path = root + '/hw/arm/Kconfig'
s = open(kconfig_path).read()
if "config UMS9230" not in s:
    s += "\nconfig UMS9230\n    bool\n    default y\n    select PL011\n    select ARM_GICV3\n"
    open(kconfig_path, 'w').write(s)
print("ums9230 machine registered; ARM CPU patched for Secure-EL1 reset")
EOF

mkdir -p "$QEMU_DIR/build"
cd "$QEMU_DIR/build"
../configure --target-list=aarch64-softmmu --without-default-features \
  --disable-tools --disable-docs
ninja qemu-system-aarch64
echo "built: $QEMU_DIR/build/qemu-system-aarch64"
