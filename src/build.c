#include "build.h"

void build_asm_fcts(){
    build_getchar();
    build_putchar();
    build_getint();
    build_putint();
}

void build_getchar(){
    FILE * file = try(fopen("_getchar.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global _getchar\n");
    fprintf(file, "push 0\n");
    fprintf(file, "mov rax, 0\n");
    fprintf(file, "mov rdi, 0\n");
    fprintf(file, "mov rsi, rsp\n");
    fprintf(file, "mov rdx, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

void build_putchar(){
    FILE * file = try(fopen("_putchar.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global _putchar\n");
    fprintf(file, "push rdi\n");
    fprintf(file, "mov rax, 1\n");
    fprintf(file, "mov rdi, 1\n");
    fprintf(file, "mov rsi, rsp\n");
    fprintf(file, "mov rdx, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

void build_getint(){
    FILE * file = try(fopen("_getint.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global _getint\n");
    fprintf(file, "push 0\n");
    fprintf(file, "mov rax, 0\n");
    fprintf(file, "mov rdi, 0\n");
    fprintf(file, "mov rsi, rsp\n");
    fprintf(file, "mov rdx, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

void build_putint(){
    FILE * file = try(fopen("_putint.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global putint\n");
    fprintf(file, "putint:\n");
    fprintf(file, "mov rax, 1\n");
    fprintf(file, "mov rdi, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

