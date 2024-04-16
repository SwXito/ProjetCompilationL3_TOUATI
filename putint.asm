section .text
global putint
putint:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    call print_int
    pop ebp
    ret