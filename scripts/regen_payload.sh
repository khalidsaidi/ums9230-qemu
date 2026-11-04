#!/bin/sh
# trustos_a.img[0x200:] -> build/trustos-payload.bin
set -e
cd "$(dirname "$0")/.."
mkdir -p build
python3 - <<'EOF'
d = open('firmware/trustos_a.img','rb').read()
open('build/trustos-payload.bin','wb').write(d[0x200:])
print('payload written to build/trustos-payload.bin (%d bytes)' % (len(d) - 0x200))
EOF
