#include "semantic.h"

/**
 * Checks the type of a given node in the abstract syntax tree.
 * 
 * @param root The root node of the abstract syntax tree.
 * @param global_vars The symbol table for global variables.
 * @param decl_functs An array of symbol tables for declared functions.
 * @param nb_functions The number of declared functions.
 * @return The type of the node:
 *         - INT if the node is a number.
 *         - CHAR if the node is a character.
 *         - The type of the variable if the node is a variable.
 *         - UNKNOWN if the node is of an unknown type.
 */
static int check_node_type(Node *root, SymbolsTable* global_vars, SymbolsTable **decl_functs, int nb_functions){
    switch(root->label){
        case Num:
            return INT;
        case Character:
            return CHAR;
        case Variable:;
            int type;
            if((type = find_type_in_sb(FIRSTCHILD(root)->ident, global_vars)) == -1){
                for(int i = 0; i < nb_functions * 2; ++i)
                    if((type = find_type_in_sb(FIRSTCHILD(root)->ident, decl_functs[i])) >= 0)
                        return type;
            }
            else
                return type;
        default:
            return UNKNOWN;
    }
}

/**
 * Checks if the given node contains an assignment of a char value to an int variable.
 * Prints a warning message if such assignment is detected.
 *
 * @param root The root node of the syntax tree.
 * @param global_vars The symbol table for global variables.
 * @param decl_functs The array of symbol tables for declared functions.
 * @param nb_functions The number of declared functions.
 */
static void check_affect(Node *root, SymbolsTable* global_vars, SymbolsTable **decl_functs, int nb_functions){
    if(root){
        if(check_node_type(FIRSTCHILD(root), global_vars, decl_functs, nb_functions) == CHAR){ //If the firstChild is a char
            switch(SECONDCHILD(root)->label){ //Check if the second child is an int
                case Expression:
                    if(expression_type(SECONDCHILD(root)) == INT)
                        fprintf(stderr, "Warning line : %d, You are putting a char in an int\n", root->lineno);
                    break;
                default:
                    if(check_node_type(SECONDCHILD(root), global_vars, decl_functs, nb_functions) == INT)
                        fprintf(stderr, "Warning, You are putting a char in an int\n");
            }
        }
    }
}

/**
 * Recursively checks the affectations in the given syntax tree.
 * 
 * @param root The root node of the syntax tree.
 * @param global_vars The symbol table for global variables.
 * @param decl_functs The symbol table for declared functions.
 * @param nb_functions The nb_functions of declared functions.
 */
void check_affectations(Node *root, SymbolsTable* global_vars, SymbolsTable **decl_functs, int nb_functions){
    if(root){
        if(root->label == Equals){
            check_affect(root, global_vars, decl_functs, nb_functions);
        }
        check_affectations(FIRSTCHILD(root), global_vars, decl_functs, nb_functions);
        check_affectations(root->nextSibling, global_vars, decl_functs, nb_functions);
    }
}

/**
 * @brief Checks if a variable is declared in the global variables or declared functions.
 *
 * This function traverses the abstract syntax tree (AST) rooted at 'root'. If a node with label 'Variable' is found,
 * it checks if the variable is declared in the global variables or in any of the declared functions. If the variable
 * is not declared, an error message is printed to stderr.
 *
 * The function is recursive and applies the same check to the first child and next sibling of 'root'.
 *
 * @param global_vars A pointer to the symbol table of global variables.
 * @param decl_functions A pointer to an array of symbol tables for declared functions. Each function has two symbol tables,
 * one for parameters and one for local variables, stored consecutively in the array.
 * @param nb_functions The number of declared functions. This is used to iterate over 'decl_functions'.
 * @param root A pointer to the root of the AST to check.
 */
void check_decl(SymbolsTable *global_vars, SymbolsTable **decl_functions, int nb_functions, Node *root){
    if(root) {
        if (root->label == Variable) {
            int is_declared = 0;
            char *s = FIRSTCHILD(root)->label == Array ? FIRSTCHILD(root)->firstChild->ident : FIRSTCHILD(root)->ident;
            for (int i = 0; i < nb_functions * 2; ++i)
                if (check_in_table(*decl_functions[i], s))
                    is_declared = 1;
            if (check_in_table(*global_vars, s))
                is_declared = 1;
            if (!is_declared){
                fprintf(stderr, "Error: variable %s is not declared\n", s);
                exit(SEMANTIC_ERROR);
            }
        }
        check_decl(global_vars, decl_functions, nb_functions, FIRSTCHILD(root));
        check_decl(global_vars, decl_functions, nb_functions, root->nextSibling);
    }
}

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