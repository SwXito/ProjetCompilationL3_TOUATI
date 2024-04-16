#include "build.h"

void build_asm_fcts(){
    build_getchar();
    build_putchar();
    build_getint();
    build_putint();
}

void build_getchar(){
    FILE * file = try(fopen("getchar.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global getchar\n");
    fprintf(file, "getchar:\n");
    fprintf(file, "mov rax, 0\n");
    fprintf(file, "mov rdi, 0\n");
    fprintf(file, "syscall\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

void build_putchar(){
    FILE * file = try(fopen("putchar.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global putchar\n");
    fprintf(file, "putchar:\n");
    fprintf(file, "mov rax, 1\n");
    fprintf(file, "mov rdi, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

void build_getint(){
    FILE * file = try(fopen("getint.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global getint\n");
    fprintf(file, "getint:\n");
    fprintf(file, "mov rax, 0\n");
    fprintf(file, "mov rdi, 0\n");
    fprintf(file, "syscall\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

void build_putint(){
    FILE * file = try(fopen("putint.asm", "w"), NULL);
    fprintf(file, "section .text\n");
    fprintf(file, "global putint\n");
    fprintf(file, "putint:\n");
    fprintf(file, "mov rax, 1\n");
    fprintf(file, "mov rdi, 1\n");
    fprintf(file, "syscall\n");
    fprintf(file, "ret\n");
    try(fclose(file));
}

