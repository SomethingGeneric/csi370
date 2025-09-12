; CSI-370 Hall
; Activity 3.1 - Syntax Translation
; Matt C 9/12/25

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

_main:
    mov BYTE [letter], 0x77
    mov DWORD [r], 0x5
    mov DWORD [s], 0x2
    mov WORD [x], 0xa
    mov WORD [y], 0x4
    mov ax, WORD [x]
    add ax, WORD [y]
    mov WORD [z], ax
    mov ax, WORD [x]
    sub ax, WORD [y]
    mov WORD [z], ax
    mov edx, 0x0
    mov eax, DWORD [r]
    mov ecx, DWORD [s]
    div ecx
    mov DWORD [t], eax
    mov edx, 0x0
    mov eax, DWORD [r]
    mov ecx, DWORD [s]
    div ecx
    mov DWORD [t], edx

    mov rax, 0x2000001      ; the GAS source had the hex, so i did too
    xor rdi, rdi            ; exit code 0
    syscall                 ; invoke syscall
