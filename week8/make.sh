#!/usr/bin/env bash

# Matt C 10-19-25
# CSI 370 w/ Brian Hall
# Assignment 8.1 Cylinder volume

# (Helper script I wrote)

if [[ "$1" == "clean" ]]; then
    [[ -f *.o ]] && rm *.o
    [[ -f program ]] && rm program
    echo "clean done."
    echo "hint: run w/o '$1' to build"
    exit
fi

nasm -f elf64 prog.asm -o main.o
g++ -c prog.cpp -o io.o
g++ main.o io.o -o program
chmod +x program