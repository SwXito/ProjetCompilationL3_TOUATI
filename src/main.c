#include "compile.h"
#include "semantic.h"
#include "build.h"
#include "parse.h"

extern Node *node;

/**
 * Pour les variables en NASM, mettre dans la section .bss avec :    global_vars : resb
 * resb pour allouer la mémoire
 * pour lire dans la mémoire (movsx rax qword [global_vars + 15])
 */

int main(int argc, char *argv[]){
    SymTabs **decl_functions = NULL;
    SymTabs *global_vars = creatSymbolsTable();

    int err = yyparse(), nb_func = count_functions();

    //Find types of expressions in the program.
    //in_depth_course(node, NULL, NULL, find_types, NULL, NULL);

    fill_global_vars(global_vars);
    build_global_vars_asm(global_vars);
    decl_functions = fill_decl_functions(nb_func, global_vars);

    if(err == 0)
        parse_args(argc, argv, node, global_vars, decl_functions, nb_func);

    semantic_check(global_vars, decl_functions, nb_func);

    deleteTree(node);
    free_symbols_table(global_vars);
    free_tables(decl_functions, nb_func);
    return err;
}