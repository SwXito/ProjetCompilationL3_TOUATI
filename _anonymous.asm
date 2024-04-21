global _start
.text:
_start:
mov rax, 2
push rax
mov rax, 50
push rax
pop rcx
pop rax
imul rax, rcx
push rax
mov rax, 1
push rax
mov rax, 60
mov rdi, 0
syscall
