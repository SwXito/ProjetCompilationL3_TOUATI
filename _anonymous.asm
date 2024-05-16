section .bss
global_vars resb 21
global _start
section .text
_start:
;Function getint
pop rax
mov byte [global_vars + 20], al
movsx rax, dword [global_vars + 4]
push rax
movsx rax, dword [global_vars + 8]
push rax
pop rcx
pop rax
cmp rax, rcx
je _l_label2
mov rax, 0
jmp _l_label3
_l_label2:
mov rax, 1
_l_label3:
push rax
movsx rax, dword [global_vars + 4]
push rax
movsx rax, dword [global_vars + 12]
push rax
pop rcx
pop rax
cmp rax, rcx
jg _l_label4
mov rax, 0
jmp _l_label5
_l_label4:
mov rax, 1
_l_label5:
push rax
pop rax
cmp rax, 0
jne _l_label0
pop rax
cmp rax, 0
jne _l_label0
mov rax, 0
jmp _l_label1
_l_label0:
mov rax, 1
_l_label1:
push rax
pop rax
cmp rax, 0
je _l_label6
mov rax, 0
jmp _l_label7
_l_label6:
mov rax, 1
_l_label7:
push rax
pop rax
mov dword [global_vars + 4], eax
mov rax, 60
mov rdi, 0
syscall
