#include "compile.h"

/**
 * @brief Checks if a symbol exists in the symbol table.
 * @param t The symbol table to check_in_table.
 * @param s The symbol to check_in_table for.
 * @return 1 if the symbol exists, 0 otherwise.
 */
int check_in_table(SymbolsTable t, char *s){
    for(Table *current = t.first; current; current = current->next)
        if (strcmp(current->var.ident, s) == 0)
            return 1;
    return 0;
}

int count_functions(){
    Node *current = FIRSTCHILD(SECONDCHILD(node));
    int nb_functions = 0;
    while(current){
        if(current->label == Function)
            nb_functions++;
        current = current->nextSibling;
    }
    return nb_functions;
}

/**
 * Finds the type of a variable in the given symbols table.
 *
 * @param var_name The name of the variable to search for.
 * @param table The symbols table to search in.
 * @return The type of the variable (0 for char, 1 for int), or -1 if the variable is not found.
 */
int find_type_in_sb(char *var_name, SymbolsTable *table){
    for (Table *current = table->first; current; current = current->next)
        if (strcmp(current->var.ident, var_name) == 0)
            return current->var.is_int;
    return -1;
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

/**
 * @brief Creates a new symbol table.
 * @return A pointer to the newly created symbol table.
 */
SymbolsTable* creatSymbolsTable(){
    SymbolsTable* sb = (SymbolsTable*) try(malloc(sizeof(SymbolsTable)), NULL);
    sb->first = NULL;
    sb->offset = 0;
    return sb;
}

/**
 * @brief Checks the type of a given identifier.
 * @param type The identifier to check_in_table.
 * @return 0 if the type is "char", 1 if the type is "int", -1 otherwise.
 */
static int check_type(char * type){
    if(strcmp(type, "char") == 0)
        return CHAR;
    if(strcmp(type, "int") == 0)
        return INT;
    return UNKNOWN;
}

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
 * @brief Adds a node to the symbol table.
 * @param t The symbol table to add to.
 * @param root The node to add.
 * @param type The type of the node.
 */
static void add_to_table(SymbolsTable *t, Node *root, char * type){
    if(!check_in_table(*t, root->ident)){
        Table *table = (Table*) try(malloc(sizeof(Table)), NULL);

        table->var.ident = strdup(root->ident);
        table->var.is_int = check_type(type);
        table->var.lineno = root->lineno;

        table->var.deplct = t->offset;
        if(table->var.is_int)
            t->offset += 4; //4 bytes for an int
        else
            t->offset += 1; //1 byte for a char
        table->next = t->first;
        t->first = table;
    }
}

/**
 * @brief Fills a symbol table with variables from a given node.
 * @param t The symbol table to fill.
 * @param root The node to get variables from.
 */
void fill_table_vars(SymbolsTable *t, Node *root){
    Node * tmp = NULL;
    if(root->label == Type && FIRSTCHILD(root))
        tmp = FIRSTCHILD(root);
    while(tmp){
        if(tmp->label == Array)
            add_to_table(t, FIRSTCHILD(tmp), root->ident);
        else
            add_to_table(t, tmp, root->ident);
        tmp = tmp->nextSibling;
    }
}

/**
 * Fills the function variables in the symbol table.
 * 
 * @param root The root node of the abstract syntax tree.
 * @return The symbol table containing the function variables.
 */
static SymbolsTable* fill_func_vars(Node *root){
    SymbolsTable *t = creatSymbolsTable();
    Node *tmp = SECONDCHILD(root)->nextSibling->nextSibling->firstChild;
    while(tmp){
        if(tmp->label == Type && FIRSTCHILD(tmp)){
            if(FIRSTCHILD(tmp)->label == Array)
                add_to_table(t, FIRSTCHILD(tmp)->firstChild, tmp->ident);
            else
                add_to_table(t, FIRSTCHILD(tmp), tmp->ident);
        }
        tmp = tmp->nextSibling;
    }
    return t;
}

/**
 * @brief Fills a symbol table with functions from a given node.
 * @param global_vars The symbol table for global variables.
 * @param t The symbol table to fill.
 * @param root The node to get functions from.
 * @param nb_functions A pointer to the nb_functions of functions.
 */
void fill_table_fcts(SymbolsTable **t, SymbolsTable *global_vars, Node *root, int *nb_functions){
    Node * tmp = root;
    if(tmp->label == Function){
        if(!strcmp(SECONDCHILD(tmp)->ident, "main"))
            build_minimal_asm(tmp, global_vars);
        t[(*nb_functions) * 2] = fill_func_parameters_table(tmp);
        t[(*nb_functions) * 2 + 1] = fill_func_vars(tmp);
        (*nb_functions)++;
    }
}

/**
 * @brief Fills a symbol table with function parameters from a given node.
 * @param root The node to get function parameters from.
 * @param nb_functions A pointer to the nb_functions of function parameters.
 * @return A pointer to the filled symbol table.
 */
SymbolsTable* fill_func_parameters_table(Node *root){
    SymbolsTable* res = creatSymbolsTable();
    in_depth_course(SECONDCHILD(root)->nextSibling->firstChild, NULL, fill_table_vars, NULL, res, NULL);
    return res;
}

/**
 * @brief Fills a symbol table with declared functions.
 * @param nb_functions A pointer to the nb_functions of declared functions.
 * @return A pointer to the filled symbol table.
 */
SymbolsTable** fill_decl_functions(int nb_func, SymbolsTable *global_vars){
    int nb_functions = 0;
    SymbolsTable** all_tables = (SymbolsTable**) try(malloc(sizeof(SymbolsTable*) * (nb_func * 2)), NULL);
    if(FIRSTCHILD(node))
        in_width_course(SECONDCHILD(node)->firstChild, fill_table_fcts, all_tables, global_vars, &nb_functions);
    return all_tables;
}

/**
 * @brief Fills a symbol table with global variables.
 * @param t The symbol table to fill.
 */
void fill_global_vars(SymbolsTable* t){
    if(FIRSTCHILD(node))
        in_depth_course(FIRSTCHILD(node)->firstChild, NULL, fill_table_vars, NULL,  t, NULL);
}

/**
 * @brief Traverses a tree in depth.
 * @param node The root node of the tree.
 * @param calc A function to perform calculations on the nodes.
 * @param table A function to fill the symbol table.
 * @param check A function to check specifications on the nodes.
 * @param t The symbol table to fill.
 * @param file The file to write to.
 */
void in_depth_course(Node * root, int (*calc)(Node *, FILE *, SymbolsTable *), void (*table)(SymbolsTable *, Node *), void (*check)(Node *), SymbolsTable *t, FILE * file){
    if(root) {
        if (calc)
            if (calc(root, file, t))
                return;
        if (table)
            table(t, root);
        if(check)
            check(root);
        in_depth_course(FIRSTCHILD(root), calc, table, check, t, file);
        in_depth_course(root->nextSibling, calc, table, check, t, file);
    }
}

/**
 * @brief Traverses a tree in width.
 * @param node The root node of the tree.
 * @param func A function to fill the symbol table.
 * @param t The symbol table to fill.
 * @param nb_functions A pointer to the nb_functions of nodes.
 */
void in_width_course(Node * root, void (*func)(SymbolsTable **, SymbolsTable *, Node *, int *), SymbolsTable **t, SymbolsTable *global_vars, int *nb_functions){
    if(root){
        func(t, global_vars, root, nb_functions);
        in_width_course(root->nextSibling, func, t, global_vars, nb_functions);
    }
}

/**
 * @brief Performs calculations on two operands and writes the result to a file.
 * @param file The file to write to.
 * @param left_op The left operand.
 * @param right_op The right operand.
 */
static void calc_to_asm(FILE * file){
    fprintf(file, "pop rcx\n");
    fprintf(file, "pop rax\n");
}

/**
 * Calculates the value if there is only one child.
 *
 * This function calculates the value of one child and writes the corresponding assembly code to the given file.
 *
 * @param file The file to write the assembly code to.
 * @return 0 if the calculation is successful.
 */
static int calc_one_child(FILE *file){
    fprintf(file, "mov rax, 0\n");
    fprintf(file, "push rax\n");
    return 0;
}

/**
 * @brief Performs addition or subtraction operation on the operands of a node and writes the result to a file.
 * @param root The node whose operands are to be operated on.
 * @param file The file to write the assembly instructions to.
 * @return The result of the addition or subtraction operation.
 */
static int addsub_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    int left_op, right_op;
    if(SECONDCHILD(root)){
        left_op = get_value(FIRSTCHILD(root), file, global_vars);
        right_op = get_value(SECONDCHILD(root), file, global_vars);
    }
    else{
        left_op = calc_one_child(file);
        right_op = get_value(FIRSTCHILD(root), file, global_vars);
    }
    calc_to_asm(file); // Write the assembly instructions for the calculation to the file.
    if(root->ident[0] == '+'){
        fprintf(file, "add rax, rcx\n");
        fprintf(file, "push rax\n");
        return left_op + right_op;
    }
    else{
        fprintf(file, "sub rax, rcx\n");
        fprintf(file, "push rax\n");
        return left_op - right_op;
    }
}

/**
 * @brief Performs multiplication or division operation on the operands of a node and writes the result to a file.
 * @param root The node whose operands are to be operated on.
 * @param file The file to write the assembly instructions to.
 * @return The result of the multiplication or division operation.
 */
static int divstar_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    int left_op = get_value(FIRSTCHILD(root), file, global_vars);
    int right_op = get_value(SECONDCHILD(root), file, global_vars);
    calc_to_asm(file); // Write the assembly instructions for the calculation to the file.
    if(root->ident[0] == '*'){
        fprintf(file, "imul rax, rcx\n");
        fprintf(file, "push rax\n");
        return left_op * right_op;
    }
    else{
        fprintf(file, "mov rdx, 0\n");
        fprintf(file, "idiv rcx\n");
        fprintf(file, "push rax\n");
        return left_op / right_op;
    }
}

/**
 * @brief Writes the value of a node to a file as an assembly instruction.
 * @param root The node whose value is to be written.
 * @param file The file to write the assembly instruction to.
 * @return The value of the node.
 */
static int num_calc(Node *root, FILE * file){
    fprintf(file, "mov rax, %d\n", root->num);
    fprintf(file, "push rax\n");
    return root->num;
}

static int ident_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    int offset = 0, type;
    for(Table *current = global_vars->first; current; current = current->next)
        if(!strcmp(current->var.ident, root->ident)){
            offset = current->var.deplct;
            type = current->var.is_int;
        }
    if(type == INT){
        printf("Variable %s is an int\n", root->ident);
        fprintf(file, "movsx rax, dword [global_vars + %d]\n", offset);
        fprintf(file, "push rax\n");
    }
    else if (type == CHAR){
        printf("Variable %s is a char\n", root->ident);
        fprintf(file, "movsx rax, byte [global_vars + %d]\n", offset);
        fprintf(file, "push rax\n");
    }
    else{
        fprintf(stderr, "Error: unknown type\n");
        exit(SEMANTIC_ERROR);
    }
    return 0;
}

static int character_calc(Node *root, FILE * file){
    fprintf(file, "mov rax, %d\n", root->ident[1]);
    fprintf(file, "push rax\n");
    return root->ident[1];
}

int get_value(Node * root, FILE * file, SymbolsTable * global_vars){
    switch(root->label){
        case Variable:
            return ident_calc(FIRSTCHILD(root), file, global_vars);
        case Num:
            return num_calc(root, file);
        case Character:
            return character_calc(root, file);
        case Expression:;
            if(FIRSTCHILD(root)->label == Addsub || FIRSTCHILD(root)->label == Divstar)
                return do_calc(FIRSTCHILD(root), file, global_vars);
            int type = expression_type(root);
            if(type == INT)
                return get_value(FIRSTCHILD(root), file, global_vars);
            else if(type == CHAR)
                return ident_calc(FIRSTCHILD(root), file, global_vars);
            else{
                fprintf(stderr, "Error line %d: unknown type\n", root->lineno);
                exit(SEMANTIC_ERROR);
            }
        default:
            fprintf(stderr, "Error line %d: unknown type\n", root->lineno);
            exit(SEMANTIC_ERROR);
    }
}

/**
 * @brief Performs calculations on a node and writes the result to a file.
 * @param root The node to perform calculations on.
 * @param file The file to write to.
 * @param global_vars The symbol table for global variables.
 * @return The result of the calculation.
 */
int do_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    switch(root->label){
        case Addsub:
            return addsub_calc(root, file, global_vars);
        case Divstar:
            return divstar_calc(root, file, global_vars);
        default:
            return 0;
    }
}

/**
 * Returns the maximum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The maximum of the two integers.
 */
static int max(int a, int b){
    if(a >= b)
        return a;
    return b;
}

/**
 * Calculates the type of a given syntax tree node.
 * 
 * @param root The root node of the syntax tree.
 * @return The type of the node. Returns -2 if the node is NULL.
 */
int expression_type(Node *root){
    if(root){
        int type;
        switch(root->label){
            case Num:
                type = INT;
                break;
            case Character:
                type = CHAR;
                break;
            case Function:
                if(!strcmp(FIRSTCHILD(root)->ident, "getchar"))
                    type = CHAR;
                else if(!strcmp(FIRSTCHILD(root)->ident, "getint"))
                    type = INT;
                else
                    type = UNKNOWN;
                break;
            default:
                type = UNKNOWN;
        }
        return max(type, max(expression_type(FIRSTCHILD(root)), expression_type(root->nextSibling)));
    }
    return VOID;
}

/**
 * Finds the types of nodes in the given tree and prints them.
 *
 * @param root The root node of the tree.
 */
void find_types(Node *root){
    if(root->label == Expression)
        print_type(expression_type(FIRSTCHILD(root)));
}

/**
 * Builds the assembly code for global variables.
 * 
 * @param t The symbols table containing the global variables.
 */
void build_global_vars_asm(SymbolsTable *t){
    FILE * file = try(fopen("_anonymous.asm", "w"), NULL);
    int size = 0;
    fprintf(file, "section .bss\n");
    for(Table *current = t->first; current; current = current->next)
        size += current->var.is_int ? 4 : 1;
    fprintf(file, "global_vars resb %d\n", size);
    try(fclose(file));
}

/**
 * @brief Builds minimal assembly code from a tree and writes it to a file.
 * @param root The root node of the tree.
 */
void build_minimal_asm(Node *root, SymbolsTable *global_vars){
    FILE * file = try(fopen("_anonymous.asm", "a"), NULL);
    fprintf(file, "global _start\n");
    fprintf(file, ".text:\n");
    fprintf(file, "_start:\n");
    in_depth_course(FIRSTCHILD(root), do_calc, NULL, NULL, global_vars, file);
    fprintf(file, "mov rax, 60\n");
    fprintf(file,  "mov rdi, 0\n");
    fprintf(file, "syscall\n");
    try(fclose(file));
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

static int get_function_type(Node *root){
    if(!strcmp(FIRSTCHILD(root)->ident, "char"))
        return CHAR;
    else if(!strcmp(FIRSTCHILD(root)->ident, "int"))
        return INT;
    else if(!strcmp(FIRSTCHILD(root)->ident, "void"))
        return VOID;
    else{
        fprintf(stderr, "Error at line %d: unknown function type\n", FIRSTCHILD(root)->lineno);
        exit(SEMANTIC_ERROR);
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

/**
 * @brief Frees the memory allocated for a table.
 * @param t The table to free.
 */
void free_table(Table *t){
    if(t){
        free_table(t->next);
        free(t->var.ident);
        free(t);
    }
}

/**
 * @brief Frees the memory allocated for a symbol table.
 * @param t The symbol table to free.
 */
void free_symbols_table(SymbolsTable *t){
    free_table(t->first); ///< Free the first table in the symbol table.
    free(t); ///< Free the symbol table itself.
}

/**
 * @brief Frees the memory allocated for multiple symbol tables.
 * @param tables The array of symbol tables to free.
 * @param length The number of symbol tables in the array.
 */
void free_tables(SymbolsTable** tables, int length){
    for(int i = 0; i < length; ++i){
        free_symbols_table(tables[i * 2]); ///< Free the symbol table at index i * 2.
        free_symbols_table(tables[i * 2 + 1]); ///< Free the symbol table at index i * 2 + 1.
    }
    free(tables); ///< Free the array of symbol tables.
}

/**
 * Prints the type based on the given integer value.
 *
 * @param type The integer value representing the type.
 */
void print_type(int type){
    switch(type){
        case INT:
            printf("It's an int\n");
            break;
        case CHAR:
            printf("It's a char\n");
            break;
        case VOID:
            printf("It's a void\n");
        default:
            printf("Unknown type\n");
    }
}

/**
 * @brief Prints a table.
 * @param t The table to print.
 */
void print_table(Table *t){
    if(t){
        printf("ident: %s Deplct : %d, type : %d\n", t->var.ident, t->var.deplct, t->var.is_int); ///< Print the identifier, displacement, and type of the variable in the table.
        print_table(t->next); ///< Recursively print the next table.
    }
}

/**
 * @brief Prints the global variables in a symbol table.
 * @param t The symbol table to print from.
 */
void print_global_vars(SymbolsTable *t){
    printf("\nGlobal vars:\n\n"); ///< Print a header for the global variables.
    print_table(t->first); ///< Print the first table in the symbol table.
}

/**
 * @brief Prints the declared functions in an array of symbol tables.
 * @param t The array of symbol tables to print from.
 * @param nb_functions The number of symbol tables in the array.
 */
void print_decl_functions(SymbolsTable **t, int nb_functions){
    printf("Functions:\n"); ///< Print a header for the functions.
    for(int i = 0; i < nb_functions; i += 2){
        printf("\nFunction %d :\n", i/2 + 1); ///< Print the function number.
        printf("\nParameters :\n"); ///< Print a header for the parameters.
        print_table(t[i]->first); ///< Print the first table in the symbol table at index i * 2.
        printf("\nVariables :\n"); ///< Print a header for the variables.
        print_table(t[i + 1]->first); ///< Print the first table in the symbol table at index i * 2 + 1.
    }
}