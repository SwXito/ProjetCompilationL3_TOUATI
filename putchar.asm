section .text
global putchar
putchar:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    push eax
    call _putchar
    add esp, 4
    pop ebp
    ret