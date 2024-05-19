section .text
global _getint
extern show_registers
extern _getchar

_getint:
    mov r12, 0 ; on met 0 dans r12
    mov r10, 1 ; on met 1 dans r10
    call _getchar ; on récupère un caractère
    cmp rax, 45 ; on compare avec '-'
    jne test_digit ; si c'est pas '-' on teste si c'est un chiffre
    mov r10, -1 ; si c'est '-' on met -1 dans r10
read_digit:
    call _getchar ; on récupère un caractère
test_digit:
    cmp rax, 48 ; on compare avec '0'
    jl end_read_digit ; si c'est plus petit que 0 on arrête
    cmp rax, 57 ; on compare avec '9'
    jg end_read_digit ; si c'est plus grand que 9 on arrête
    sub rax, 48 ; on convertit le caractère en entier
    imul r12, 10 ; on multiplie le chiffre par 10
    add r12, rax ; on ajoute le chiffre
    jmp read_digit ; on recommence
end_read_digit: 
    mov rax, r12 ; on met le résultat dans rax
    imul rax, r10 ; on multiplie par -1 si besoin
    ret
