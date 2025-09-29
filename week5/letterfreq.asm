; Matt C 9-28-25
; CSI 370 w/ Brian Hall
; Assignment 5.2 Letter frequency

section .data
    tstr db 'Assembly is the best programming language!', 0xa 
    tstr_len equ $ - tstr     ; Length of the string

section .text
    global _main

_main:
    mov esi, tstr ; string pointer
    xor ecx, ecx ; Counter register

    mov edx, tstr_len ; length of string

    count_loop:
    cmp edx, 0
    je done_counting

    lodsb ; load byte [esi] into al and increment esi

    ; Check if 'A'
    cmp al, 'A'
    je found

    ; Check if 'a'
    cmp al, 'a'
    je found

    ; Loop else
    jmp continue_loop

    found:
    inc ecx ; inc the counter

    continue_loop:
    dec edx
    jmp count_loop

    done_counting:

    ; exit(0)
    mov rax, 60             ; syscall number for exit
    xor rdi, rdi            ; exit code 0
    syscall                 ; invoke syscall
