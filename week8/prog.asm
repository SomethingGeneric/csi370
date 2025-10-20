; Matt C 10-19-25
; CSI 370 w/ Brian Hall
; Assignment 8.1 Cylinder volume

default rel

section .data
    prompt_radius db "Enter radius: ", 0
    prompt_height db "Enter height: ", 0
    prompt_volume db "Volume: ", 0
    pi_const     dq 3.1415926535897932384626433832795

section .text
    global _asmMain
    extern _printString
    extern _getDouble
    extern _printDouble

_asmMain:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    ; prompt for radius
    lea rdi, [rel prompt_radius]
    call _printString
    call _getDouble
    movsd [rbp-8], xmm0

    ; prompt for height
    lea rdi, [rel prompt_height]
    call _printString
    call _getDouble
    movsd [rbp-16], xmm0

    ; compute volume = pi * (radius^2) * height
    fld qword [rbp-8]
    fld st0 
    fmulp st1, st0
    fld qword [pi_const]
    fmulp st1, st0
    fld qword [rbp-16]
    fmulp st1, st0
    fstp qword [rbp-24]

    ; print result
    lea rdi, [rel prompt_volume]
    call _printString
    movsd xmm0, [rbp-24]
    call _printDouble

    mov rax, 60
    xor rdi, rdi
    syscall
