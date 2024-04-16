section .text
global getchar
getchar:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 3
    mov ebx, 0
    mov ecx, esp
    mov edx, 1
    int 0x80
    mov eax, [esp]
    add esp, 4
    pop ebp
    ret