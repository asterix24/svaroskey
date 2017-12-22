#!/bin/bash

DIR="$(dirname "${BASH_SOURCE[0]}")"

if [ $# -lt 2 ]; then
    echo "Usage: $0 <dev> <bin>"
    exit 1
fi

DEV="$1"
BIN="$2"

if [ ! -e "$DEV" ]; then
    echo "$DEV: no such file or directory"
    exit 1
fi

if [ ! -f "$BIN" ]; then
    echo "$BIN: no such file or directory"
    exit 1
fi

"$DIR/stm32flash" -w "$BIN" -b 115200 "$DEV"
