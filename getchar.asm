section .text
global _getchar

_getchar:
push 0 ; on initialise 1 octet sur la pile à 0
mov rax, 0 ; utilisé par syscall pour savoir qu'il faut lire
mov rdi, 0 ; fichier depuis lequelle on lit
mov rsi, rsp ; zone mémoire ou on veut copier les données
mov rdx, 1 ; nombre d'octets qu'on veut lire
syscall ; appel système
pop rax ; on récupére l'octets lu depuis la pile
ret