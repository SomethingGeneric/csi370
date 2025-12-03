#!/usr/bin/env bash

# Matt C 11/12/25
# CSI 370 w/ Brian Hall
# Assignment 9.1 Inline ASM multiply/divide helper

# (Helper script I wrote)

set -e

if [[ "$1" == "clean" ]]; then
    [[ -f inline_mul ]] && rm inline_mul
    [[ -f inline_mul.o ]] && rm inline_mul.o
    echo "clean done."
    echo "hint: run w/o '$1' to build"
    exit 0
fi

g++ -std=c++17 -Wall -Wextra -c inline_mul.cpp -o inline_mul.o
g++ inline_mul.o -o inline_mul
chmod +x inline_mul
