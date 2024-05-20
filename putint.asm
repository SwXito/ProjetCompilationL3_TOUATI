section .text
extern _putchar
global _putint
_putint:
    mov rax, rdi ; On recupère n
    cmp rax, 0 ; On compare n à 0
    jge is_positive ; Si n est positif ou 0, sauter à is_positive
    push rax ; On empile n
    mov rdi, '-' ; On met le signe moins dans rdi
    mov r11, rsp
    sub rsp, 8
    and rsp, -16
    mov qword [rsp], r11
    call _putchar ; On affiche le signe moins
    pop rsp
    pop rax ; On dépile n
    neg rax ; rendre n positif
is_positive:
    mov r10, 0 ; On met le compteur de chiffres à 0
convert_loop:
    mov rdx, 0 ; On met rdx à 0
    mov rbx, 10 ; On met rbx à 10
    div rbx ; On divise rax par rbx et on met le reste dans rdx
    add rdx, '0'
    push rdx ; On empile le reste
    inc r10 ; On incrémente le compteur de chiffres
    cmp rax, 0 ; On compare rax à 0
    jne convert_loop
print_loop:
    dec r10 ; On décrémente le compteur de chiffres
    mov rax, 1 ; On veut ecrire
    mov rdi, 1 ; Sur la sortie standard
    mov rsi, rsp ; On met le reste dans rsi
    mov rdx, 1 ; On veut lire un octet
    syscall ; On appelle le systeme
    pop r12 ; On dépile le reste
    cmp r10, 0
    jne print_loop ; si i n'est pas 0, continuer la boucle
    ret
