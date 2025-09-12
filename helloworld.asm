section .data
    hello db 'Hello, world!', 0xa 
    hello_len equ $ - hello      ; Length of the string

section .text
    global _main

_main:
    ; write(1, hello, hello_len)
    mov rax, 1              ; syscall number for write
    mov rdi, 1              ; file descriptor 1 (stdout)
    mov rsi, hello          ; pointer to the string
    mov rdx, hello_len      ; length of the string
    syscall                 ; invoke syscall

    ; exit(0)
    mov rax, 60             ; syscall number for exit
    xor rdi, rdi            ; exit code 0
    syscall                 ; invoke syscall
