#include "compile.h"
#include "semantic.h"
#include "build.h"
#include "parse.h"

extern Node *node;

int main(int argc, char *argv[]){
    SymTabs **decl_functions = NULL;
    SymTabs *global_vars = creatSymbolsTable();
    SymTabs *functions = creatSymbolsTable();
    
    int err = yyparse(), nb_func = count_functions();
    

    //Find types of expressions in the program.
    //in_depth_course(node, NULL, NULL, find_types, NULL, NULL);

    fill_global_vars(global_vars);
    build_global_vars_asm(global_vars);
    fill_functions(functions, SECONDCHILD(node)->firstChild);
    decl_functions = fill_decl_functions(nb_func, global_vars);

    semantic_check(global_vars, decl_functions, nb_func, functions);

    if(err == 0){
        parse_args(argc, argv, node, global_vars, decl_functions, nb_func);
        deleteTree(node);
    }

    print_global_vars(functions);
    free_symbols_table(global_vars);
    free_tables(decl_functions, nb_func);
    free_symbols_table(functions);
    return err;
}