#include "build.h"

static void build_getchar(FILE *file){
    fprintf(file, "_getchar:\n");
    fprintf(file, "push 0 ; on initialise 1 octet sur la pile à 0\n");
    fprintf(file, "mov rax, 0 ; utilisé par syscall pour savoir qu'il faut lire\n");
    fprintf(file, "mov rdi, 0 ; fichier depuis lequelle on lit\n");
    fprintf(file, "mov rsi, rsp ; zone mémoire ou on veut copier les données\n");
    fprintf(file, "mov rdx, 1 ; nombre d'octets qu'on veut lire\n");
    fprintf(file, "syscall ; appel système\n");
    fprintf(file, "pop rax ; on récupére l'octets lu depuis la pile\n");
    fprintf(file, "ret\n");
}

static void build_getint(FILE *file){
    fprintf(file, "_getint:\n") ;
    fprintf(file, "mov r12, 0 ; on met 0 dans r12\n") ;
    fprintf(file, "mov r10, 1 ; on met 1 dans r10\n") ;
    fprintf(file, "mov r11, rsp\n") ;
    fprintf(file, "sub rsp, 8\n") ;
    fprintf(file, "and rsp, -16\n") ;
    fprintf(file, "mov qword [rsp], r11\n") ;
    fprintf(file, "call _getchar ; on récupère un caractère\n") ;
    fprintf(file, "pop rsp\n") ;
    fprintf(file, "cmp rax, 45 ; on compare avec '-'\n") ;
    fprintf(file, "jne test_digit ; si c'est pas '-' on teste si c'est un chiffre\n") ;
    fprintf(file, "mov r10, -1 ; si c'est '-' on met -1 dans r10\n") ;
    fprintf(file, "read_digit:\n") ;
    fprintf(file, "mov r11, rsp\n") ;
    fprintf(file, "sub rsp, 8\n") ;
    fprintf(file, "and rsp, -16\n") ;
    fprintf(file, "mov qword [rsp], r11\n") ;
    fprintf(file, "call _getchar ; on récupère un caractère\n") ;
    fprintf(file, "pop rsp\n") ;
    fprintf(file, "test_digit:\n") ;
    fprintf(file, "cmp rax, 48 ; on compare avec '0'\n") ;
    fprintf(file, "jl end_read_digit ; si c'est plus petit que 0 on arrête\n") ;
    fprintf(file, "cmp rax, 57 ; on compare avec '9'\n") ;
    fprintf(file, "jg end_read_digit ; si c'est plus grand que 9 on arrête\n") ;
    fprintf(file, "sub rax, 48 ; on convertit le caractère en entier\n") ;
    fprintf(file, "imul r12, 10 ; on multiplie le chiffre par 10\n") ;
    fprintf(file, "add r12, rax ; on ajoute le chiffre\n") ;
    fprintf(file, "jmp read_digit ; on recommence\n") ;
    fprintf(file, "end_read_digit:\n") ;
    fprintf(file, "mov rax, r12 ; on met le résultat dans rax\n") ;
    fprintf(file, "imul rax, r10 ; on multiplie par -1 si besoin\n") ;
    fprintf(file, "ret\n") ;
}

static void build_putchar(FILE *file){
    fprintf(file, "_putchar:\n");
    fprintf(file, "push rdi\n");
    fprintf(file, "mov rax, 1\n");
    fprintf(file, "mov rdi, 1\n");
    fprintf(file, "mov rsi, rsp\n");
    fprintf(file, "mov rdx, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "ret\n");
}

static void build_putint(FILE *file){
    fprintf(file, "_putint:\n");
    fprintf(file, "mov rax, rdi ; On recupère n\n");
    fprintf(file, "cmp rax, 0 ; On compare n à 0\n");
    fprintf(file, "jge is_positive ; Si n est positif ou 0, sauter à is_positive\n");
    fprintf(file, "push rax ; On empile n\n");
    fprintf(file, "mov rdi, '-' ; On met le signe moins dans rdi\n");
    fprintf(file, "mov r11, rsp\n");
    fprintf(file, "sub rsp, 8\n");
    fprintf(file, "and rsp, -16\n");
    fprintf(file, "mov qword [rsp], r11\n");
    fprintf(file, "call _putchar ; On affiche le signe moins\n");
    fprintf(file, "pop rsp\n");
    fprintf(file, "pop rax ; On dépile n\n");
    fprintf(file, "neg rax ; rendre n positif\n");
    fprintf(file, "is_positive:\n");
    fprintf(file, "mov r10, 0 ; On met le compteur de chiffres à 0\n");
    fprintf(file, "convert_loop:\n");
    fprintf(file, "mov rdx, 0 ; On met rdx à 0\n");
    fprintf(file, "mov rbx, 10 ; On met rbx à 10\n");
    fprintf(file, "div rbx ; On divise rax par rbx et on met le reste dans rdx\n");
    fprintf(file, "add rdx, '0'\n");
    fprintf(file, "push rdx ; On empile le reste\n");
    fprintf(file, "inc r10 ; On incrémente le compteur de chiffres\n");
    fprintf(file, "cmp rax, 0 ; On compare rax à 0\n");
    fprintf(file, "jne convert_loop\n");
    fprintf(file, "print_loop:\n");
    fprintf(file, "dec r10 ; On décrémente le compteur de chiffres\n");
    fprintf(file, "mov rax, 1 ; On veut ecrire\n");
    fprintf(file, "mov rdi, 1 ; Sur la sortie standard\n");
    fprintf(file, "mov rsi, rsp ; On met le reste dans rsi\n");
    fprintf(file, "mov rdx, 1 ; On veut lire un octet\n");
    fprintf(file, "syscall ; On appelle le systeme\n");
    fprintf(file, "pop r12 ; On dépile le reste\n");
    fprintf(file, "cmp r10, 0\n");
    fprintf(file, "jne print_loop ; si i n'est pas 0, continuer la boucle\n");
    fprintf(file, "ret\n");
}

void build_external_fcts(FILE *file){
    build_getchar(file);
    build_getint(file);
    build_putchar(file);
    build_putint(file);
}