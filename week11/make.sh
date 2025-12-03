#!/usr/bin/env bash

set -euo pipefail

if [[ "${1:-}" == "clean" ]]; then
    rm -f copy_file.o copy_file copied_output.txt
    echo "clean done."
    exit 0
fi

nasm -f elf64 copy_file.asm -o copy_file.o
ld copy_file.o -o copy_file
chmod +x copy_file
echo "copy_file built. Run ./copy_file to perform the copy."
