section .text
global _putchar
_putchar:
push rdi
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 1
syscall
pop rax
ret