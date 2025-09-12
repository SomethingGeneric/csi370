; Hall CSI-370 Assignment 3.2
; 9/12/25 - Matt C

section .data
    message: ; multi-line str
      DB "You already know what the next",0ah
      DB "variable will be, don't you?", 0ah
    length equ $ - message ; Length of the message str
    length5 equ $ + 5 ; length plus five

section .text
    global _main ; run my function pls!

_main:

    add WORD [length5], 1 ; add 1 to the val of length5

    ; do i get brownie points for looking up how to write to stdout?
    mov rax, 1              ; syscall number for write
    mov rdi, 1              ; file descriptor 1 (stdout)
    mov rsi, message        ; pointer to the string
    mov rdx, length         ; length of the string
    syscall                 ; invoke syscall


    mov rax, 60  ; exit program syscall value
    xor rdi, rdi ; i dont understand the purpose of this tbh
    syscall      ; now we exit the program