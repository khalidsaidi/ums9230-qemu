#!/bin/sh
# Run the ums9230 machine against the (patched) trustos payload.
set -e
cd "$(dirname "$0")/.."
QEMU_DIR="${QEMU_DIR:-qemu}"
timeout 8 "$QEMU_DIR/build/qemu-system-aarch64" -machine ums9230 -cpu max \
  -kernel build/trustos-payload.bin -nographic 2>&1 | grep -a '\[DBG\]' | tail -20
