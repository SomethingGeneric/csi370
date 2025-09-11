#!/usr/bin/env bash

if [[ "$1" == "" ]]; then
    printf "Path: "
    read TF
else
    TF="$1"
fi

[[ ! -d work ]] && mkdir work

cp "$TF" work/.
cd work

nasm -f elf64 -o temp.o ${TF##*/}
ld -e _main -melf_x86_64 -o program temp.o
cp program ../
cd ../
rm -rf work

echo "start prog..."
echo
./program