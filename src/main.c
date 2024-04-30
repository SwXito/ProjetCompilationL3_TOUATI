#include "compile.h"
#include "build.h"
#include "parse.h"

extern Node *node;

/**
 * Pour les variables en NASM, mettre dans la section .bss avec :    global_vars : resb
 * resb pour allouer la mémoire
 * pour lire dans la mémoire (movsx rax qword [global_vars + 15])
 */

int main(int argc, char *argv[]){
    SymbolsTable **decl_functions = NULL;
    SymbolsTable *global_vars = creatSymbolsTable();

    int count = 0;
    int err = yyparse();

    //Find types of expressions in the program.
    in_depth_course(node, NULL, NULL, find_types, NULL, NULL);

    fill_global_vars(global_vars);
    decl_functions = fill_decl_functions(&count);

    if(err == 0)
        parse_args(argc, argv, node, global_vars, decl_functions, count);

    check_decl(global_vars, decl_functions, count, node->firstChild->nextSibling);

    deleteTree(node);
    free_symbols_table(global_vars);
    free_tables(decl_functions, count);
    return err;
}