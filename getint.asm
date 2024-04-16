section .text
global getint
getint:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 3
    mov [ebp-4], eax
    mov eax, [ebp+8]
    mov [eax], [ebp-4]
    mov eax, [ebp+8]
    mov eax, [eax]
    mov esp, ebp
    pop ebp
    ret