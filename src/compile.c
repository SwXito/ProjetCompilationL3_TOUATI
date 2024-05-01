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

/**
 * Finds the type of a variable in the given symbols table.
 *
 * @param var_name The name of the variable to search for.
 * @param table The symbols table to search in.
 * @return The type of the variable (0 for int, 1 for float), or -1 if the variable is not found.
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
 * @param count The number of declared functions. This is used to iterate over 'decl_functions'.
 * @param root A pointer to the root of the AST to check.
 */
void check_decl(SymbolsTable *global_vars, SymbolsTable **decl_functions, int count, Node *root){
    if(root) {
        if (root->label == Variable) {
            int is_declared = 0;
            char *s = FIRSTCHILD(root)->label == Array ? FIRSTCHILD(root)->firstChild->ident : FIRSTCHILD(root)->ident;
            for (int i = 0; i < count * 2; ++i)
                if (check_in_table(*decl_functions[i], s))
                    is_declared = 1;
            if (check_in_table(*global_vars, s))
                is_declared = 1;
            if (!is_declared)
                fprintf(stderr, "Error: variable %s is not declared\n", s);
        }
        check_decl(global_vars, decl_functions, count, FIRSTCHILD(root));
        check_decl(global_vars, decl_functions, count, root->nextSibling);
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
        return 0;
    if(strcmp(type, "int") == 0)
        return 1;
    return -1;
}

/**
 * Checks the type of a given node in the abstract syntax tree.
 * 
 * @param root The root node of the abstract syntax tree.
 * @param global_vars The symbol table for global variables.
 * @param decl_functs An array of symbol tables for declared functions.
 * @param count The number of declared functions.
 * @return The type of the node:
 *         - 1 if the node is a number.
 *         - 0 if the node is a character.
 *         - The type of the variable if the node is a variable.
 *         - -1 if the node is of an unknown type.
 */
static int check_node_type(Node *root, SymbolsTable* global_vars, SymbolsTable **decl_functs, int count){
    switch(root->label){
        case Num:
            return 1;
        case Character:
            return 0;
        case Variable:;
            int type;
            if((type = find_type_in_sb(FIRSTCHILD(root)->ident, global_vars)) == -1){
                for(int i = 0; i < count * 2; ++i)
                    if((type = find_type_in_sb(FIRSTCHILD(root)->ident, decl_functs[i])) >= 0)
                        return type;
            }
            else
                return type;
        default:
            return -1;
    }
}

/**
 * Checks if the given node contains an assignment of a char value to an int variable.
 * Prints a warning message if such assignment is detected.
 *
 * @param root The root node of the syntax tree.
 * @param global_vars The symbol table for global variables.
 * @param decl_functs The array of symbol tables for declared functions.
 * @param count The number of declared functions.
 */
static void check_affect(Node *root, SymbolsTable* global_vars, SymbolsTable **decl_functs, int count){
    if(root){
        if(check_node_type(FIRSTCHILD(root), global_vars, decl_functs, count) == 0){ //If the firstChild is a char
            switch(SECONDCHILD(root)->label){ //Check if the second child is an int
                case Expression:
                    if(calc_type(SECONDCHILD(root)))
                        fprintf(stderr, "Warning, You are putting a char in an int\n");
                    break;
                default:
                    if(check_node_type(SECONDCHILD(root), global_vars, decl_functs, count))
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
 * @param count The count of declared functions.
 */
void check_affectations(Node *root, SymbolsTable* global_vars, SymbolsTable **decl_functs, int count){
    if(root){
        if(root->label == Equals){
            check_affect(root, global_vars, decl_functs, count);
        }
        check_affectations(FIRSTCHILD(root), global_vars, decl_functs, count);
        check_affectations(root->nextSibling, global_vars, decl_functs, count);
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

        table->var.deplct = t->offset;
        if(table->var.is_int)
            t->offset += 4;
        else
            t->offset += 1;
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
 * @param t The symbol table to fill.
 * @param root The node to get functions from.
 * @param count A pointer to the count of functions.
 */
void fill_table_fcts(SymbolsTable **t, Node *root, int *count){
    Node * tmp = root;
    if(tmp->label == Function){
        if(!strcmp(SECONDCHILD(tmp)->ident, "main"))
            build_minimal_asm(tmp);
        t[(*count) * 2] = fill_func_parameters_table(tmp);
        t[(*count) * 2 + 1] = fill_func_vars(tmp);
        (*count)++;
    }
}

/**
 * @brief Fills a symbol table with function parameters from a given node.
 * @param root The node to get function parameters from.
 * @param count A pointer to the count of function parameters.
 * @return A pointer to the filled symbol table.
 */
SymbolsTable* fill_func_parameters_table(Node *root){
    SymbolsTable* res = creatSymbolsTable();
    in_depth_course(SECONDCHILD(root)->nextSibling->firstChild, NULL, fill_table_vars, NULL, res, NULL);
    return res;
}

/**
 * @brief Fills a symbol table with declared functions.
 * @param count A pointer to the count of declared functions.
 * @return A pointer to the filled symbol table.
 */
SymbolsTable** fill_decl_functions(int *count){
    SymbolsTable** all_tables = (SymbolsTable**) try(malloc(sizeof(SymbolsTable*) * 20), NULL);
    if(FIRSTCHILD(node))
        in_width_course(SECONDCHILD(node)->firstChild, fill_table_fcts, all_tables, count);
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
void in_depth_course(Node * root, int (*calc)(Node *, FILE *), void (*table)(SymbolsTable *, Node *), void (*check)(Node *), SymbolsTable *t, FILE * file){
    if(root) {
        if (calc)
            if (calc(root, file))
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
 * @param count A pointer to the count of nodes.
 */
void in_width_course(Node * root, void (*func)(SymbolsTable **, Node *, int *), SymbolsTable **t, int *count){
    if(root){
        func(t, root, count);
        in_width_course(root->nextSibling, func, t, count);
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
static int addsub_calc(Node *root, FILE * file){
    int left_op, right_op;
    if(SECONDCHILD(root)){
        left_op = do_calc(FIRSTCHILD(root), file);
        right_op = do_calc(SECONDCHILD(root), file);
    }
    else{
        left_op = calc_one_child(file);
        right_op = do_calc(FIRSTCHILD(root), file);
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
static int divstar_calc(Node *root, FILE * file){
    int left_op = do_calc(FIRSTCHILD(root), file);
    int right_op = do_calc(SECONDCHILD(root), file);
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

/**
 * @brief Performs calculations on a node and writes the result to a file.
 * @param root The node to perform calculations on.
 * @param file The file to write to.
 * @return The result of the calculation.
 */
int do_calc(Node *root, FILE * file){
    switch(root->label){
        case Return:
            return -1;
        case Array:
            return -1;
        case Addsub:
            return addsub_calc(root, file);
        case Divstar:
            return divstar_calc(root, file);
        case Num:
            return num_calc(root, file);
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
int calc_type(Node *root){
    if(root){
        int type;
        switch(root->label){
            case Num:
                type =  1;
                break;
            case Character:
                type =  0;
                break;
            case Function:
                if(!strcmp(FIRSTCHILD(root)->ident, "getchar"))
                    type = 0;
                else if(!strcmp(FIRSTCHILD(root)->ident, "getint"))
                    type = 1;
                else
                    type = -1;
                break;
            default:
                type = -1;
        }
        return max(type, max(calc_type(FIRSTCHILD(root)), calc_type(root->nextSibling)));
    }
    return -2;
}

/**
 * Finds the types of nodes in the given tree and prints them.
 *
 * @param root The root node of the tree.
 */
void find_types(Node *root){
    if(root->label == Expression)
        print_type(calc_type(FIRSTCHILD(root)));
}

/**
 * @brief Builds minimal assembly code from a tree and writes it to a file.
 * @param root The root node of the tree.
 */
void build_minimal_asm(Node *root){
    FILE * file = try(fopen("_anonymous.asm", "w"), NULL);
    fprintf(file, "global _start\n");
    fprintf(file, ".text:\n");
    fprintf(file, "_start:\n");
    in_depth_course(FIRSTCHILD(root), do_calc, NULL, NULL, NULL, file);
    fprintf(file, "mov rax, 60\n");
    fprintf(file,  "mov rdi, 0\n");
    fprintf(file, "syscall\n");
    try(fclose(file));
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
        case 1:
            printf("It's an int\n");
            break;
        case 0:
            printf("It's a char\n");
            break;
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
 * @param count The number of symbol tables in the array.
 */
void print_decl_functions(SymbolsTable **t, int count){
    printf("Functions:\n"); ///< Print a header for the functions.
    for(int i = 0; i < count; ++i){
        printf("\nFunction %d :\n", i+1); ///< Print the function number.
        printf("\nParameters :\n"); ///< Print a header for the parameters.
        print_table(t[i * 2]->first); ///< Print the first table in the symbol table at index i * 2.
        printf("\nVariables :\n"); ///< Print a header for the variables.
        print_table(t[i * 2 + 1]->first); ///< Print the first table in the symbol table at index i * 2 + 1.
    }
}