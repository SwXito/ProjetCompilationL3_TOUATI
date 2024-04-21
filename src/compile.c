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
            char *s = root->firstChild->label == Array ? root->firstChild->firstChild->ident : root->firstChild->ident;
            for (int i = 0; i < count; ++i)
                if (check_in_table(*decl_functions[i * 2], s))
                    is_declared = 1;
            if (check_in_table(*global_vars, s))
                is_declared = 1;
            if (!is_declared)
                fprintf(stderr, "Error: variable %s is not declared\n", s);
        }
        check_decl(global_vars, decl_functions, count, root->firstChild);
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
            t->offset += 8;
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
    if(root->label == Type && root->firstChild)
        tmp = root->firstChild;
    while(tmp){
        if(tmp->label == Array)
            add_to_table(t, tmp->firstChild, root->ident);
        else
            add_to_table(t, tmp, root->ident);
        tmp = tmp->nextSibling;
    }
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
        if(!strcmp(tmp->firstChild->nextSibling->ident, "main"))
            build_minimal_asm(tmp);
        SymbolsTable *new_table = creatSymbolsTable();
        t[(*count) * 2] = fill_func_parameters_table(tmp);
        fill_table_vars(new_table, tmp->firstChild->nextSibling->nextSibling->nextSibling->firstChild);
        t[(*count) * 2 + 1] = new_table;
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
    in_depth_course(root->firstChild->nextSibling->nextSibling->firstChild, NULL, fill_table_vars, res, NULL);
    return res;
}

/**
 * @brief Fills a symbol table with declared functions.
 * @param count A pointer to the count of declared functions.
 * @return A pointer to the filled symbol table.
 */
SymbolsTable** fill_decl_functions(int *count){
    SymbolsTable** all_tables = (SymbolsTable**) try(malloc(sizeof(SymbolsTable*) * 10), NULL);
    if(node->firstChild)
        in_width_course(node->firstChild->nextSibling->firstChild, fill_table_fcts, all_tables, count);
    return all_tables;
}

/**
 * @brief Fills a symbol table with global variables.
 * @param t The symbol table to fill.
 */
void fill_global_vars(SymbolsTable* t){
    if(node->firstChild)
        in_depth_course(node->firstChild->firstChild, NULL, fill_table_vars,  t, NULL);
}

/**
 * @brief Traverses a tree in depth.
 * @param node The root node of the tree.
 * @param calc A function to perform calculations on the nodes.
 * @param table A function to fill the symbol table.
 * @param t The symbol table to fill.
 * @param file The file to write to.
 */
void in_depth_course(Node * root, int (*calc)(Node *, FILE *), void (*table)(SymbolsTable *, Node *), SymbolsTable *t, FILE * file){
    if(root) {
        if (calc)
            if (calc(root, file))
                return;
        if (table)
            table(t, root);
        in_depth_course(root->firstChild, calc, table, t, file);
        in_depth_course(root->nextSibling, calc, table, t, file);
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
 * @brief Performs addition or subtraction operation on the operands of a node and writes the result to a file.
 * @param root The node whose operands are to be operated on.
 * @param file The file to write the assembly instructions to.
 * @return The result of the addition or subtraction operation.
 */
static int addsub_calc(Node *root, FILE * file){
    int left_op = do_calc(root->firstChild, file);
    int right_op = do_calc(root->firstChild->nextSibling, file);
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
    int left_op = do_calc(root->firstChild, file);
    int right_op = do_calc(root->firstChild->nextSibling, file);
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
    if(root->label == Addsub)
        return addsub_calc(root, file);
    else if(root->label == Divstar)
        return divstar_calc(root, file);
    else if(root->label == Num)
        return num_calc(root, file);
    else
        return 0;
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
    in_depth_course(root->firstChild, do_calc, NULL, NULL, file);
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
    printf("\nFunctions:\n"); ///< Print a header for the functions.
    for(int i = 0; i < count; ++i){
        printf("\nFunction %d :\n", i+1); ///< Print the function number.
        printf("\nParameters :\n"); ///< Print a header for the parameters.
        print_table(t[i * 2]->first); ///< Print the first table in the symbol table at index i * 2.
        printf("\nVariables :\n"); ///< Print a header for the variables.
        print_table(t[i * 2 + 1]->first); ///< Print the first table in the symbol table at index i * 2 + 1.
    }
}