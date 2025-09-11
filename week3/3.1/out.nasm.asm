; syntax trans submission
; nasm 64 bit

section .data
    ; nil

section .bss

letter: resb 1
r: resd 1
s: resd 1
t: resd 1
x: resw 1
y: resw 1
z: resw 1

section .text
    global _main

_main