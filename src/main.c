#include "compile.h"
#include "semantic.h"
#include "parse.h"

int has_suffix(const char *str, const char *suffix) {
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);
    if (len_suffix > len_str) {
        return 0;
    }
    return strncmp(str + len_str - len_suffix, suffix, len_suffix) == 0;
}

static char *get_filename(int argc, char **argv){
    char *name = malloc(sizeof(char) * 100);
    strcpy(name, "_anonymous.asm");
    for(int i = 1; i < argc-1; i++)
        if(argv[i][0] != '<' && has_suffix(argv[i+1], ".tpc")){
            strcpy(name, argv[i+1]);
            strstr(name, ".tpc")[0] = '\0';
            strcat(name, ".asm");
        }
    return name;
} 

static void compile(int argc, char **argv){
    SymTabs *global_vars = creatSymbolsTable();
    SymTabsFct **functions = NULL;

    char *filename = get_filename(argc, argv);
    int err = yyparse(), nb_func = count_functions();

    fill_global_vars(global_vars);
    build_global_vars_asm(global_vars, filename);
    functions = fill_decl_functions(nb_func, global_vars, filename);
    
    semantic_check(global_vars, functions, nb_func);
    if(err == 0){
        parse_args(argc, argv, node, global_vars, functions, nb_func);
        deleteTree(node);
    }

    free_symbols_table(global_vars);
    free_tables(functions, nb_func);
    free(filename);
}

int main(int argc, char *argv[]){
    /*
    mov r11, rsp
    sub rsp, 8
    and rsp, -16
    mov qword [rsp], r11
    call my_function2
    pop rsp
    */
    compile(argc, argv);
    return 0;
}