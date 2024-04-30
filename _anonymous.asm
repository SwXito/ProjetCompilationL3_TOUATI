global _start
.text:
_start:
mov rax, 1
push rax
mov rax, 2
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rax, 3
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rax, 4
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rax, 60
mov rdi, 0
syscall
