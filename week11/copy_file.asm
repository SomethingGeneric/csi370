; Matt C 12/3/25
; CSI 370 w/ Brian Hall
; Assignment 10.2 Working With Files

%define SYS_READ        0
%define SYS_WRITE       1
%define SYS_OPEN        2
%define SYS_CLOSE       3
%define SYS_EXIT        60
%define SYS_FCHMOD      91

%define STDIN_FD        0
%define STDOUT_FD       1
%define STDERR_FD       2

%define O_RDONLY        0
%define O_WRONLY        1
%define O_CREAT         64
%define O_TRUNC         512

%define DEST_PERMS      0o666
%define BUFFER_SIZE     1024

section .data
    src_path            db  "read_only_source.txt", 0
    dest_path           db  "copied_output.txt", 0

    success_msg         db  "Copy completed successfully.", 10
    success_len         equ $ - success_msg

section .bss
    buffer              resb BUFFER_SIZE

section .text
    global _start

_start:
    ; open source (read-only)
    mov     rax, SYS_OPEN
    lea     rdi, [rel src_path]
    mov     rsi, O_RDONLY
    xor     rdx, rdx
    syscall
    mov     r12, rax                    ; store source file descriptor

    ; open destination (write only, create/truncate)
    mov     rax, SYS_OPEN
    lea     rdi, [rel dest_path]
    mov     rsi, O_WRONLY | O_CREAT | O_TRUNC
    mov     rdx, DEST_PERMS
    syscall
    mov     r13, rax                    ; store destination file descriptor

copy_loop:
    mov     rax, SYS_READ
    mov     rdi, r12
    lea     rsi, [rel buffer]
    mov     rdx, BUFFER_SIZE
    syscall
    cmp     rax, 0
    je      finish_copy
    mov     r14, rax                    ; bytes read

    mov     rax, SYS_WRITE
    mov     rdi, r13
    lea     rsi, [rel buffer]
    mov     rdx, r14
    syscall
    jmp     copy_loop

finish_copy:
    ; set destination permissions to 0666 explicitly
    mov     rax, SYS_FCHMOD
    mov     rdi, r13
    mov     rsi, DEST_PERMS
    syscall

    ; close destination
    mov     rax, SYS_CLOSE
    mov     rdi, r13
    syscall

    ; close source
    mov     rax, SYS_CLOSE
    mov     rdi, r12
    syscall

    ; notify user
    mov     rax, SYS_WRITE
    mov     rdi, STDOUT_FD
    lea     rsi, [rel success_msg]
    mov     rdx, success_len
    syscall

    ; exit success
    mov     rax, SYS_EXIT
    xor     rdi, rdi
    syscall
