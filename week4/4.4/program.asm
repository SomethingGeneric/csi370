; Matt C 9-22-25 for CSI 370 w/ Brian Hall
; Assignment 4.4 - Differently Sized Arrays

section .data
    nums dw 5, 10, 15, 20
    mult dq 5
    arr_len equ 4

section .bss
    outnums resd 4

section .text
    global _main

_main:
    mov rsi, nums ; Start of src array
    mov rdi, outnums ; Start of dest array
    mov rcx, 0 ; counter = 0

    mult_loop:
        cmp rcx, arr_len ; check if we've iterated enough
        jae end_loop     ; and if so, jump to end_loop

        mov rax, [rsi + rcx * 8] ; load the element from src 
        mul qword [mult]         ; multiply rax by the multiplier val (5)
        mov [rdi + rcx * 8], rax ; move the result into the dest array
        inc rcx                  ; increment loop counter
        jmp mult_loop            ; and do it again!

    end_loop:
        ; exit(0)
        mov rax, 60             ; syscall number for exit
        xor rdi, rdi            ; exit code 0
        syscall                 ; invoke syscall
