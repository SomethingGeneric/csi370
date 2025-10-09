; Matt C 9-28-25
; CSI 370 w/ Brian Hall
; Assignment 6.1 Sum

section .text
    global main
    extern read_int
    extern print_int

main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    
    call read_int
    mov [rbp-4], eax
    
    call read_int
    mov [rbp-8], eax
    
    mov eax, [rbp-4]
    add eax, [rbp-8]
    
    mov edi, eax
    call print_int
    
    xor eax, eax
    mov rsp, rbp
    pop rbp
    ret