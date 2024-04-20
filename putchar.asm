section .text
global _putchar
_putchar:
push rdi ; on initialise 1 octet sur la pile à 0
mov rax, 1 ; utilisé par syscall pour savoir qu'il faut lire
mov rdi, 1 ; fichier depuis lequelle on écrit
mov rsi, rsp ; zone mémoire ou on veut copier les données
mov rdx, 1 ; nombre d'octets qu'on veut lire
syscall ; appel système
pop rax ; on récupére l'octets lu depuis la pile
ret