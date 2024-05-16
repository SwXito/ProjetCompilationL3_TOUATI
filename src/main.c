#include "compile.h"
#include "semantic.h"
#include "build.h"
#include "parse.h"

extern Node *node;

int main(int argc, char *argv[]){
    SymTabs *global_vars = creatSymbolsTable();
    SymTabsFct **functions = NULL;
    
    int err = yyparse(), nb_func = count_functions();

    fill_global_vars(global_vars);
    build_global_vars_asm(global_vars);
    functions = fill_decl_functions(nb_func, global_vars);

    semantic_check(global_vars, functions, nb_func);

    if(err == 0){
        parse_args(argc, argv, node, global_vars, functions, nb_func);
        deleteTree(node);
    }

    free_symbols_table(global_vars);
    free_tables(functions, nb_func);
    return err;
}