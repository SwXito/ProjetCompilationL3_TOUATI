section .text
section .data
number: dd 0
buffer: db "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"
global _getint

_getint:
    mov rax, 0
    mov rdi, 0
    mov rsi, buffer
    mov rdx, 4
    syscall
    
    mov rax, number
    ret

transform:
