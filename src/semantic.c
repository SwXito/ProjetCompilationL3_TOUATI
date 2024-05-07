#include "semantic.h"

static void check_different_idents(SymbolsTable *first, SymbolsTable *second){
    for(Table *current = first->first; current; current = current->next)
        if(check_in_table(*second, current->var.ident)){
            fprintf(stderr, "Error at line %d: variable %s is declared in the function and is a parameter\n", current->var.lineno, current->var.ident);
            exit(SEMANTIC_ERROR);
        }
}

static void check_return_type(Node *root, int type){
    if(root){
        if(root->label == Return){
            if(expression_type(FIRSTCHILD(root)) != type){
                if(type == INT)
                    fprintf(stderr, "Error at line %d: return type is not int\n", root->lineno);
                else if(type == CHAR)
                    fprintf(stderr, "Error at line %d: return type is not char\n", root->lineno);
                else if(type == VOID)
                    fprintf(stderr, "Error at line %d: return type is not void\n", root->lineno);
                else
                    fprintf(stderr, "Error at line %d: unknown return type\n", root->lineno);
                exit(SEMANTIC_ERROR);
            }
        }
        check_return_type(FIRSTCHILD(root), type);
        check_return_type(root->nextSibling, type);
    }
}

static void check_idents(SymbolsTable *global_vars, SymbolsTable **decl_functions, int nb_functions){
    Node *current = FIRSTCHILD(SECONDCHILD(node));
    for(int i = 0; i < nb_functions; i += 2)
        check_different_idents(decl_functions[i], decl_functions[i+1]);
    check_decl(global_vars, decl_functions, nb_functions, node->firstChild->nextSibling);
    while(current){
        if(current->label == Function){
            if(check_in_table(*global_vars, SECONDCHILD(current)->ident)){
                fprintf(stderr, "Error at line %d: function %s has the same name as a global variable\n", SECONDCHILD(current)->lineno, SECONDCHILD(current)->ident);
                exit(SEMANTIC_ERROR);
            }
        }
        current = current->nextSibling;
    }
}

static void check_existing_main(Node *root){
    int exist = 0;
    while(root){
        if(root->label == Function && !strcmp(SECONDCHILD(root)->ident, "main")){
            exist = 1;
            if(get_function_type(root) != INT){
                fprintf(stderr, "Error at line %d: main function must return an int\n", SECONDCHILD(root)->lineno);
                exit(SEMANTIC_ERROR);
            }
        }
        root = root->nextSibling;
    }
    if(!exist){
        fprintf(stderr, "Error: main function not found\n");
        exit(SEMANTIC_ERROR);
    }
}

static void check_functions(){
    Node *current = FIRSTCHILD(SECONDCHILD(node));
    int function_type; //-2 Unknown, -1 void, 0 for char, 1 for int
    check_existing_main(current);
    while(current){
        if(current->label == Function){
            function_type = get_function_type(current);
            check_return_type(FIRSTCHILD(FOURTHCHILD(current)), function_type);
        }
        current = current->nextSibling;
    }
}

static void check_types(SymbolsTable *global_vars, SymbolsTable **decl_functions, int nb_functions){
    check_affectations(node, global_vars, decl_functions, nb_functions);
    return;
}

static void check_arrays(){
    return;
}

/**
 * @brief Checks the semantics of the program.
 */
void semantic_check(SymbolsTable *global_vars, SymbolsTable **decl_functions, int nb_functions){
    check_idents(global_vars, decl_functions, nb_functions);
    check_functions();
    check_types(global_vars, decl_functions, nb_functions);
    check_arrays();
}