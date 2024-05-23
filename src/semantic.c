#include "semantic.h"

static void check_reserved_idents(char **reserved_idents, int nb_reserved, Node *root){
    for(int i = 0; i < nb_reserved; ++i)
        if(!strcmp(root->ident, reserved_idents[i])){
            fprintf(stderr, "Error at line %d: %s is a reserved identifier\n", root->lineno, root->ident);
            exit(SEMANTIC_ERROR);
        }
}

static int left_value_type(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    int type;
    switch(FIRSTCHILD(root)->label){
        case Array:
            for(int i = 0; i < nb_functions; ++i)
                if(function_name && !strcmp(functions[i]->ident, function_name)){
                    if((type = find_type_in_fct(FIRSTCHILD(FIRSTCHILD(root))->ident, functions[i])) >= 0)
                        return type;
                    if((type = find_type_in_sb(FIRSTCHILD(FIRSTCHILD(root))->ident, global_vars)) >= 0)
                        return type;
                }
            return UNKNOWN;
        default:
            for(int i = 0; i < nb_functions; ++i)
                if(function_name && !strcmp(functions[i]->ident, function_name)){
                    if((type = find_type_in_fct(FIRSTCHILD(root)->ident, functions[i])) >= 0)
                        return type;
                    if((type = find_type_in_sb(FIRSTCHILD(root)->ident, global_vars)) >= 0)
                        return type;
                }
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
static void check_affect(Node *root, SymTabs* global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    if(root){
        if(expression_type(SECONDCHILD(root), global_vars, functions, nb_functions, function_name) == VOID){
            fprintf(stderr, "Error at line %d: void value cannot be assigned to a variable\n", root->lineno);
            exit(SEMANTIC_ERROR);
        }
        if(left_value_type(FIRSTCHILD(root), global_vars, functions, nb_functions, function_name) == CHAR){ //If the firstChild is a char
            if(expression_type(FIRSTCHILD(SECONDCHILD(root)), global_vars, functions, nb_functions, function_name) == INT)
                fprintf(stderr, "Warning line : %d, You are putting an int in a char\n", root->lineno);
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
void check_affectations(Node *root, SymTabs* global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    if(root){
        if(root->label == Function && (FIRSTCHILD(root)->label == Type || FIRSTCHILD(root)->label == Void))
            function_name = SECONDCHILD(root)->ident;
        if(root->label == Equals){
            printf("Checking affectation\n");
            check_affect(root, global_vars, functions, nb_functions, function_name);
            printf("Affectation checked\n");
        }
        check_affectations(FIRSTCHILD(root), global_vars, functions, nb_functions, function_name);
        check_affectations(root->nextSibling, global_vars, functions, nb_functions, function_name);
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
 * @param functions A pointer to an array of symbol tables for declared functions. Each function has two symbol tables,
 * one for parameters and one for local variables, stored consecutively in the array.
 * @param nb_functions The number of declared functions. This is used to iterate over 'functions'.
 * @param root A pointer to the root of the AST to check.
 */
static void check_decl_in_fct(SymTabs *global_vars, SymTabsFct **functions, int nb_functions, Node *root, char **reserved_idents, int nb_reserved, char *function_name){
    if(root) {
        if(root->label == Function && (FIRSTCHILD(root)->label == Type || FIRSTCHILD(root)->label == Void)){
            function_name = SECONDCHILD(root)->ident;
        }
        if (root->label == Variable) {
            int is_declared = 0;
            char *s = FIRSTCHILD(root)->label == Array ? FIRSTCHILD(root)->firstChild->ident : FIRSTCHILD(root)->ident;
            for (int i = 0; i < nb_functions; ++i){
                if(function_name && !strcmp(function_name, functions[i]->ident)){
                    if (check_in_table_fct(functions[i]->parameters, s) || check_in_table_fct(functions[i]->variables, s))
                        is_declared = 1;
                }
            }
            if (check_in_table(*global_vars, s))
                is_declared = 1;
            if (!is_declared){
                fprintf(stderr, "Error line %d : variable %s is not declared\n", FIRSTCHILD(root)->lineno, s);
                exit(SEMANTIC_ERROR);
            }
        }
        check_decl_in_fct(global_vars, functions, nb_functions, FIRSTCHILD(root), reserved_idents, nb_reserved, function_name);
        check_decl_in_fct(global_vars, functions, nb_functions, root->nextSibling, reserved_idents, nb_reserved, function_name);
    }
}

static void check_decl_in_globals(Node *root, char **reserved_idents, int nb_reserved){
    if(root) {
        if (root->label == Type) {
            Node *current = root;
            while(current){
                Node *var = FIRSTCHILD(current);
                while(var){
                    switch(var->label){
                        case Array:
                            check_reserved_idents(reserved_idents, nb_reserved, FIRSTCHILD(var));
                            break;
                        default:
                            check_reserved_idents(reserved_idents, nb_reserved, var);
                        }
                    var = var->nextSibling;
                }
                current = current->nextSibling;
            }
        }
    }
}

/**
 * @brief Gets the type of a function.
 *
 * This function traverses the abstract syntax tree (AST) rooted at 'root' to find the type of the function.
 * The type of the function is determined by the label of the first child of the root node.
 *
 * @param root A pointer to the root of the AST to check.
 * @return The type of the function:
 *         - INT if the function returns an integer.
 *         - CHAR if the function returns a character.
 *         - VOID if the function returns void.
 *         - UNKNOWN if the function returns an unknown type.
 */
static void check_different_idents(Table *first, Table *second){
    for(Table *current = first; current; current = current->next)
        if(check_in_table_fct(second, current->var.ident)){
            fprintf(stderr, "Error at line %d: variable %s is declared in the function and is a parameter\n", current->var.lineno, current->var.ident);
            exit(SEMANTIC_ERROR);
        }
}

static int is_ident_array_in_table(char *ident, Table *table){
    for(Table *current = table; current; current = current->next)
        if(!strcmp(ident, current->var.ident))
            return current->var.is_array;
    return -1;
}

static void check_return_type(Node *root, int function_type, SymTabs *global_vars, SymTabsFct **functions, int nb_fcts, char *function_name){
    if(root){
        if(root->label == Return){
            int return_type;
            switch(root->firstChild->label){
                case Expression:
                    return_type = expression_type(FIRSTCHILD(root), global_vars, functions, nb_fcts, function_name);
                    if(FIRSTCHILD(root)->firstChild && FIRSTCHILD(root)->firstChild->label == Variable
                     && FIRSTCHILD(FIRSTCHILD(root))->firstChild && FIRSTCHILD(FIRSTCHILD(root))->firstChild->label == Ident)
                        for(int i = 0; i < nb_fcts; ++i)
                            if(function_name && !strcmp(function_name, functions[i]->ident)){
                                if(is_ident_array_in_table(FIRSTCHILD(FIRSTCHILD(root))->firstChild->ident, global_vars->first) < 1)
                                    if(is_ident_array_in_table(FIRSTCHILD(FIRSTCHILD(root))->firstChild->ident, functions[i]->parameters) < 1)
                                        if(is_ident_array_in_table(FIRSTCHILD(FIRSTCHILD(root))->firstChild->ident, functions[i]->variables) < 1)
                                            break;
                                fprintf(stderr, "Error at line %d: %s is an array\n", FIRSTCHILD(FIRSTCHILD(root))->lineno, FIRSTCHILD(FIRSTCHILD(root))->firstChild->ident);
                                exit(SEMANTIC_ERROR);
                            }

                    break;
                default:
                    return_type = VOID;
            }       
            if(function_type == VOID){
                if(return_type != VOID){
                    fprintf(stderr, "Error at line %d: function returning void cannot return a value\n", root->lineno);
                    exit(SEMANTIC_ERROR);
                }
            } else{
                if(return_type > function_type){
                    fprintf(stderr, "Warning at line %d: function returning %s is returning %s\n", root->lineno, function_type == INT ? "an int" : "a char", return_type == INT ? "an int" : "a char");
                }
                else if(return_type <= VOID){
                    fprintf(stderr, "Warning at line %d: function returning %s should return a value\n", root->lineno, function_type == INT ? "int" : "char");
                }
            }
        }
        check_return_type(FIRSTCHILD(root), function_type, global_vars, functions, nb_fcts, function_name);
        check_return_type(root->nextSibling, function_type, global_vars, functions, nb_fcts, function_name);
    }
}

static int check_function_name(SymTabsFct **functions, int nb_functions, char *function_name, char *call_func_name){
    int is_declared = 0;
    for(int i = 0; i < nb_functions; ++i)
        if(!strcmp(functions[i]->ident, function_name))
            if(check_in_table_fct(functions[i]->variables, call_func_name) || check_in_table_fct(functions[i]->parameters, call_func_name))
                is_declared = 1;
    return is_declared;
}

static void check_idents(SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char **reserved_idents, int nb_reserved){
    char * function_name = NULL;
    Node *current = FIRSTCHILD(SECONDCHILD(node));
    for(int i = 0; i < nb_functions; i++)
        check_different_idents(functions[i]->parameters, functions[i]->variables);
    check_decl_in_globals(FIRSTCHILD(FIRSTCHILD(node)), reserved_idents, nb_reserved);
    check_decl_in_fct(global_vars, functions, nb_functions, FIRSTCHILD(SECONDCHILD(node)), reserved_idents, nb_reserved, function_name);
    while(current){
        if(current->label == Function){
            /*if(check_function_name(functions, nb_functions, SECONDCHILD(current)->ident)){
                fprintf(stderr, "Error at line %d: function %s has the same name as a parameter\n", SECONDCHILD(current)->lineno, SECONDCHILD(current)->ident);
                exit(SEMANTIC_ERROR);
            }*/
            if(check_in_table(*global_vars, SECONDCHILD(current)->ident)){
                fprintf(stderr, "Error at line %d: function %s has the same name as a global variable\n", SECONDCHILD(current)->lineno, SECONDCHILD(current)->ident);
                exit(SEMANTIC_ERROR);
            }
            for(int i = 0; i < nb_reserved; ++i)
                if(!strcmp(SECONDCHILD(current)->ident, reserved_idents[i])){
                    fprintf(stderr, "Error at line %d: function %s has the same name as a reserved function\n", SECONDCHILD(current)->lineno, SECONDCHILD(current)->ident);
                    exit(SEMANTIC_ERROR);
                }
        }
        current = current->nextSibling;
    }
}

static int decl_function_type(Node *root){
    if(!strcmp(FIRSTCHILD(root)->ident, "int"))
        return INT;
    if(!strcmp(FIRSTCHILD(root)->ident, "char"))
        return CHAR;
    if(!strcmp(FIRSTCHILD(root)->ident, "void"))
        return VOID;
    if(!strcmp(SECONDCHILD(root)->ident, "putchar") || !strcmp(SECONDCHILD(root)->ident, "getchar"))
        return VOID;
    if(!strcmp(SECONDCHILD(root)->ident, "getint"))
        return INT;
    if(!strcmp(SECONDCHILD(root)->ident, "getchar"))
        return CHAR;
    fprintf(stderr, "Error at line %d: unknown type\n", root->lineno);
    exit(SEMANTIC_ERROR);
}

static void check_existing_main(Node *root){
    int exist = 0;
    while(root){
        if(root->label == Function && !strcmp(SECONDCHILD(root)->ident, "main")){
            exist = 1;
            if(decl_function_type(root) != INT){
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

static int is_array(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    if(root){
        switch(root->label){
            case Function:
                return 0;
            case Ident:;
                int is_arr = 0;
                for(int i = 0; i < nb_functions; ++i){
                    if(function_name && !strcmp(functions[i]->ident, function_name)){
                        if((is_arr = check_is_array(root->ident, functions[i]->parameters)) >= 0){
                            if(is_arr && !FIRSTCHILD(root))
                                return 1;
                            if(is_arr && FIRSTCHILD(root)){
                                return 0; //If it is an array and it is accessed
                            }
                            return 0;
                        }
                        if((is_arr = check_is_array(root->ident, functions[i]->variables)) >= 0){
                            if(is_arr && !FIRSTCHILD(root))
                                return 1;
                            if(is_arr && FIRSTCHILD(root)){
                                return 0; //If it is an array and it is accessed
                            }
                            return 0;
                        }
                    }
                }
                if((is_arr = check_is_array(root->ident, global_vars->first)) >= 0){
                    if(is_arr && !FIRSTCHILD(root))
                        return 1;
                    if(is_arr && FIRSTCHILD(root)){
                        return 0; //If it is an array and it is not accessed
                    }
                    return 0;
                }
            default:
                return is_array(FIRSTCHILD(root), global_vars, functions, nb_functions, function_name);
        }
    }
    return 0;
}

static void comparing_args(Node *tmp, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name, int count, int *is_array, int *is_int){
        while(tmp){
        expression_type(tmp, global_vars, functions, nb_functions, function_name);
        switch(FIRSTCHILD(tmp)->label){
            case Variable:;
                int type;
                for(int i = 0; i < nb_functions; i++){
                    if(function_name && !strcmp(function_name, functions[i]->ident)){
                        if(FIRSTCHILD(tmp)->firstChild->label == Ident){
                            if(!is_array[count] && ((is_ident_array_in_table(FIRSTCHILD(tmp)->firstChild->ident, global_vars->first) == 1) 
                            || (is_ident_array_in_table(FIRSTCHILD(tmp)->firstChild->ident, functions[i]->parameters) == 1) 
                            || (is_ident_array_in_table(FIRSTCHILD(tmp)->firstChild->ident, functions[i]->variables) == 1))){
                                fprintf(stderr, "Error at line %d: can't acces to the array\n", FIRSTCHILD(tmp)->lineno);
                                exit(SEMANTIC_ERROR);
                            }
                            if(is_array[count] && ((is_ident_array_in_table(FIRSTCHILD(tmp)->firstChild->ident, global_vars->first) == 0) 
                            || (is_ident_array_in_table(FIRSTCHILD(tmp)->firstChild->ident, functions[i]->parameters) == 0) 
                            || (is_ident_array_in_table(FIRSTCHILD(tmp)->firstChild->ident, functions[i]->variables) == 0))){
                                fprintf(stderr, "Error at line %d: need an array\n", FIRSTCHILD(tmp)->lineno);
                                exit(SEMANTIC_ERROR);
                            }
                            if(is_array[count]){
                                if((type = find_type_in_fct(FIRSTCHILD(tmp)->firstChild->ident, functions[i])) < 0)
                                    type = find_type_in_sb(FIRSTCHILD(tmp)->firstChild->ident, global_vars);
                                if(type != is_int[count]){
                                    fprintf(stderr, "Error at line %d: type mismatch\n", FIRSTCHILD(tmp)->lineno);
                                    exit(SEMANTIC_ERROR);
                                }
                            }
                        }
                        if(FIRSTCHILD(tmp)->firstChild->label == Array){
                            if(is_array[count]){
                                fprintf(stderr, "Error at line %d: need an array\n", FIRSTCHILD(tmp)->lineno);
                                exit(SEMANTIC_ERROR);
                            }
                        }
                    }
                }
                break;
            default:
                if(is_array[count]){
                    fprintf(stderr, "Error at line %d: need an array\n", FIRSTCHILD(tmp)->lineno);
                    exit(SEMANTIC_ERROR);
                }
                break;
        }
        count--;
        tmp = tmp->nextSibling;
    }
}


static void check_args_affect(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name, char *call_func_name){
    if(root && root->label != Void){
        Node *tmp = root;
        int count = 0;
        static int is_array[6];
        static int is_int[6];
        for(int i = 0; i < nb_functions; i++){
            if(call_func_name && !strcmp(call_func_name, functions[i]->ident)){
                for(Table *current = functions[i]->parameters; current; current = current->next){
                    if(current->var.is_array){
                        is_array[count] = 1;
                    }
                    else{
                        is_array[count] = 0;
                    }
                    is_int[count] = current->var.is_int;
                    count++;
                }
            }
        }
        count--;
        comparing_args(tmp, global_vars, functions, nb_functions, function_name, count, is_array, is_int);
    }
}

static void check_function_call_args(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *call_func_name, char *function_name){
    if(root){
        int call_nb_params = 0, func_params = 0;
        Node *first_param = FIRSTCHILD(root);
        check_args_affect(first_param, global_vars, functions, nb_functions, function_name, call_func_name);
        while(first_param && first_param->label != Void){
            call_nb_params++;
            first_param = first_param->nextSibling;
        }
        if(!strcmp(call_func_name, "getint") || !strcmp(call_func_name, "getchar")){
            if(call_nb_params != 0){
                fprintf(stderr, "Error at line %d: function %s has 0 parameters, %d given\n", root->lineno, call_func_name, call_nb_params);
                exit(SEMANTIC_ERROR);
            }
        }else if(!strcmp(call_func_name, "putint") || !strcmp(call_func_name, "putchar")){
            if(call_nb_params != 1){
                fprintf(stderr, "Error at line %d: function %s has 1 parameter, %d given\n", root->lineno, call_func_name, call_nb_params);
                exit(SEMANTIC_ERROR);
            }
        }else{
            if(check_function_name(functions, nb_functions, function_name, call_func_name)){
                fprintf(stderr, "Error at line %d: function %s is not a function\n", root->lineno, call_func_name);
                exit(SEMANTIC_ERROR);
            }
            for(int i = 0; i < nb_functions; ++i){
                if(call_func_name && !strcmp(call_func_name, functions[i]->ident)){
                    func_params = nb_params_function(functions, nb_functions, call_func_name);
                    if(call_nb_params != func_params){
                        fprintf(stderr, "Error at line %d: function %s has %d parameters, %d given\n", FIRSTCHILD(root)->lineno, call_func_name, func_params, call_nb_params);
                        exit(SEMANTIC_ERROR);
                    }
                }
            }
        }
    }
}

static void check_function_call(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name, char **reserved_idents, int nb_reserved){
    if(root){
        if(root->label == Function){
            Node *parameters = FIRSTCHILD(root)->firstChild;
            int is_declared = 0;
            for(int i = 0; i < nb_reserved; ++i)
                if(!strcmp(FIRSTCHILD(root)->ident, reserved_idents[i]))
                    is_declared = 1;
            for(int i = 0; i < nb_functions; ++i)
                if(FIRSTCHILD(root)->ident && !strcmp(FIRSTCHILD(root)->ident, functions[i]->ident))
                    is_declared = 1;
            if(!is_declared){
                fprintf(stderr, "Error at line %d: function %s is not declared\n", FIRSTCHILD(root)->lineno, FIRSTCHILD(root)->ident);
                exit(SEMANTIC_ERROR);
            }
            check_function_call_args(parameters, global_vars, functions, nb_functions, FIRSTCHILD(root)->ident, function_name);
        }
        check_function_call(FIRSTCHILD(root), global_vars, functions, nb_functions, function_name, reserved_idents, nb_reserved);
        check_function_call(root->nextSibling, global_vars, functions, nb_functions, function_name, reserved_idents, nb_reserved);
    }
}

static void check_functions(SymTabs *global_vars, SymTabsFct **functions, int nb_fcts, char **reserved_idents, int nb_reserved){
    Node *current = FIRSTCHILD(SECONDCHILD(node));
    int function_type; //-2 Unknown, -1 void, 0 for char, 1 for int
    check_existing_main(current);
    while(current){
        if(current->label == Function){
            Node *corps = FOURTHCHILD(current);
            function_type = decl_function_type(current);
            if(find_label_return(corps))
                check_return_type(FIRSTCHILD(FOURTHCHILD(current)), function_type, global_vars, functions, nb_fcts, SECONDCHILD(current)->ident);
            else if(function_type != VOID){
                fprintf(stderr, "Warning at line %d: function %s should return a value\n", current->lineno, SECONDCHILD(current)->ident);
            }
            check_function_call(corps, global_vars, functions, nb_fcts, SECONDCHILD(current)->ident, reserved_idents, nb_reserved);
        }
        current = current->nextSibling;
    }
}

static void check_types(SymTabs *global_vars, SymTabsFct **functions, int nb_functions){
    char *function_name = NULL;
    check_affectations(node, global_vars, functions, nb_functions, function_name);
    return;
}

static void check_arith_array(Node * current, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    if(current){
        switch(current->label){
            case Or:
            case And:
            case Order:
            case Eq:
            case Equals:
            case Addsub:
            case Not:
            case Divstar:
                if(is_array(FIRSTCHILD(current), global_vars, functions, nb_functions, function_name)){
                    fprintf(stderr, "Error at line %d: can't acces to the array\n",  FIRSTCHILD(current)->lineno);
                    exit(SEMANTIC_ERROR);
                }
                if(SECONDCHILD(current) && is_array(SECONDCHILD(current), global_vars, functions, nb_functions, function_name)){
                    fprintf(stderr, "Error at line %d: can't acces to the array\n", SECONDCHILD(current)->lineno);
                    exit(SEMANTIC_ERROR);
                }
                break;
            case While:
            case If:
                if(is_array(FIRSTCHILD(current), global_vars, functions, nb_functions, function_name)){
                    fprintf(stderr, "Error at line %d: array can't be use as boolean\n", FIRSTCHILD(current)->lineno);
                    exit(SEMANTIC_ERROR);
                }
                if(is_array(SECONDCHILD(current), global_vars, functions, nb_functions, function_name)){
                    fprintf(stderr, "Error at line %d: can't acces to the array\n", SECONDCHILD(current)->lineno);
                    exit(SEMANTIC_ERROR);
                }if(THIRDCHILD(current) && is_array(THIRDCHILD(current), global_vars, functions, nb_functions, function_name)){
                    fprintf(stderr, "Error at line %d: can't acces the array\n", THIRDCHILD(current)->lineno);
                    exit(SEMANTIC_ERROR);
                }
                break;
            default:
                break;
        }
        check_arith_array(FIRSTCHILD(current), global_vars, functions, nb_functions, function_name);
        check_arith_array(current->nextSibling, global_vars, functions, nb_functions, function_name);
    }
}

static void check_valid_decl_array(Node *root){
    if(root){
        if(root->label == Type){
            Node *current = FIRSTCHILD(root);
            while(current){
                if(current->label == Array){
                    if(FIRSTCHILD(FIRSTCHILD(current))->num <= 0){
                        fprintf(stderr, "Error at line %d: array (%s) size must be greater than 0\n", FIRSTCHILD(FIRSTCHILD(current))->lineno, FIRSTCHILD(current)->ident);
                        exit(SEMANTIC_ERROR);
                    }
                }
                current = current->nextSibling;
            }
        }
        check_valid_decl_array(root->nextSibling);
    }
}

static void check_index(Node *root){
    if(root){
        if(root->label == Array){
            if(expression_result(FIRSTCHILD(FIRSTCHILD(FIRSTCHILD(root)))) < 0){
                fprintf(stderr, "Error at line %d: index acces of an array can't be negative\n", FIRSTCHILD(FIRSTCHILD(root))->lineno);
                exit(SEMANTIC_ERROR);
            }
        }
        check_index(FIRSTCHILD(root));
        check_index(root->nextSibling);
    }
}

static void check_valid_array_acces(Node *root){
    if(root){
        if(root->label == Instructions){
            check_index(FIRSTCHILD(root));
        }
        check_valid_array_acces(root->nextSibling);
    }
}

static void check_ident_not_array(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    int arr = 0;
    if(root->label == Ident){
        if((arr = is_ident_array_in_table(root->ident, global_vars->first)) == -1){
            for(int i = 0; i < nb_functions; ++i){
                if(function_name && !strcmp(function_name, functions[i]->ident)){
                    if((arr = is_ident_array_in_table(root->ident, functions[i]->parameters)) == -1)
                        arr = is_ident_array_in_table(root->ident, functions[i]->variables);
                    break;
                }
            }
        }
        if(arr == 0){
            fprintf(stderr, "Error at line %d: %s is not an array\n", root->lineno, root->ident);
            exit(SEMANTIC_ERROR);
        }
    }
}

static void check_access(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name){
    if(root){
        if(root->label == Array){
            check_ident_not_array(FIRSTCHILD(root), global_vars, functions, nb_functions, function_name);
        }
        check_access(FIRSTCHILD(root), global_vars, functions, nb_functions, function_name);
        check_access(root->nextSibling, global_vars, functions, nb_functions, function_name);
    }
}

static void check_arrays(SymTabs *global_vars, SymTabsFct **functions, int nb_functions){
    Node *globals = FIRSTCHILD(FIRSTCHILD(node));
    Node *functs = FIRSTCHILD(SECONDCHILD(node));
    while(globals){
        Node *current = FIRSTCHILD(globals);
        while(current){
            if(current->label == Array){
                if(FIRSTCHILD(FIRSTCHILD(current))->num <= 0){
                    fprintf(stderr, "Error at line %d: array (%s) size must be greater than 0\n", FIRSTCHILD(FIRSTCHILD(current))->lineno, FIRSTCHILD(current)->ident);
                    exit(SEMANTIC_ERROR);
                }
            }
            current = current->nextSibling;
        }
        globals = globals->nextSibling;
    }
    while(functs){
        check_arith_array(functs, global_vars, functions, nb_functions, SECONDCHILD(functs)->ident);
        check_valid_decl_array(FIRSTCHILD(FOURTHCHILD(functs)));
        //check_valid_array_acces(FIRSTCHILD(FOURTHCHILD(functs)));
        check_access(FIRSTCHILD(FOURTHCHILD(functs)), global_vars, functions, nb_functions, SECONDCHILD(functs)->ident);
        functs = functs->nextSibling;
    }
}

/**
 * @brief Checks the semantics of the program.
 */
void semantic_check(SymTabs *global_vars, SymTabsFct **functions, int nb_functions){
    int reserved_idents_size = 4; //change if reserved_idents is changed
    char* reserved_idents[] = {"getint", "putint", "getchar", "putchar"}; 
    check_idents(global_vars, functions, nb_functions, reserved_idents, reserved_idents_size);
    printf("Check idents done\n");
    check_functions(global_vars, functions, nb_functions, reserved_idents, reserved_idents_size);
    printf("Check functions done\n");
    check_types(global_vars, functions, nb_functions);
    printf("Check types done\n");
    check_arrays(global_vars, functions, nb_functions);
    printf("Check arrays done\n");
}