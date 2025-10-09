#!/usr/bin/env bash

# Matt C 9-28-25
# CSI 370 w/ Brian Hall
# Assignment 6.1 Sum

# (Helper script I wrote)

if [[ "$1" == "clean" ]]; then
    [[ -f *.o ]] && rm *.o
    [[ -f program ]] && rm program
    echo "clean done."
    echo "hint: run w/o '$1' to build"
    exit
fi

nasm -f elf64 main.asm -o main.o
g++ -c io.cpp -o io.o
g++ main.o io.o -o program
chmod +x program