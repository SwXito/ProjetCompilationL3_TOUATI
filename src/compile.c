#include "compile.h"

//TO DO: DEBUG TAB + DO IF ELSE

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
 * @brief Adds a node to the symbol table.
 * @param t The symbol table to add to.
 * @param root The node to add.
 * @param type The type of the node.
 */
static void add_to_table(SymbolsTable *t, Node *root, char * type, int is_array, int size){
    if(!check_in_table(*t, root->ident)){
        Table *table = (Table*) try(malloc(sizeof(Table)), NULL);

        table->var.ident = strdup(root->ident);
        table->var.is_int = check_type(type);
        table->var.lineno = root->lineno;
        table->var.is_array = is_array;
        table->var.size = size;

        table->var.deplct = t->offset;
        if(is_array)
            t->offset += size * (table->var.is_int ? 4 : 1);
        else
            t->offset += table->var.is_int ? 4 : 1;
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
            add_to_table(t, FIRSTCHILD(tmp), root->ident, 1, FIRSTCHILD(FIRSTCHILD(tmp))->num);
        else
            add_to_table(t, tmp, root->ident, 0, 0);
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
                add_to_table(t, FIRSTCHILD(tmp)->firstChild, tmp->ident, 1, FIRSTCHILD(FIRSTCHILD(tmp))->num);
            else
                add_to_table(t, FIRSTCHILD(tmp), tmp->ident, 0, 0);
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
        int skip = 0;
        if (calc)
            if((skip = calc(root, file, t)) == 1)
                return;
        if (table)
            table(t, root);
        if(check)
            check(root);
        if(skip != -1)
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
static void calc_one_child(FILE *file){
    fprintf(file, "mov rax, 0\n");
    fprintf(file, "push rax\n");
}

/**
 * @brief Performs addition or subtraction operation on the operands of a node and writes the result to a file.
 * @param root The node whose operands are to be operated on.
 * @param file The file to write the assembly instructions to.
 * @return The result of the addition or subtraction operation.
 */
static void addsub_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    if(SECONDCHILD(root)){
        get_value(FIRSTCHILD(root), file, global_vars);
        get_value(SECONDCHILD(root), file, global_vars);
    }
    else{
        calc_one_child(file);
        get_value(FIRSTCHILD(root), file, global_vars);
    }
    calc_to_asm(file); // Write the assembly instructions for the calculation to the file.
    if(root->ident[0] == '+'){
        fprintf(file, "add rax, rcx\n");
        fprintf(file, "push rax\n");
    }
    else{
        fprintf(file, "sub rax, rcx\n");
        fprintf(file, "push rax\n");
    }
}

/**
 * @brief Performs multiplication or division operation on the operands of a node and writes the result to a file.
 * @param root The node whose operands are to be operated on.
 * @param file The file to write the assembly instructions to.
 * @return The result of the multiplication or division operation.
 */
static void divstar_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    get_value(FIRSTCHILD(root), file, global_vars);
    get_value(SECONDCHILD(root), file, global_vars);
    calc_to_asm(file); // Write the assembly instructions for the calculation to the file.
    if(root->ident[0] == '*'){
        fprintf(file, "imul rax, rcx\n");
        fprintf(file, "push rax\n");
    }
    else{
        fprintf(file, "mov rdx, 0\n");
        fprintf(file, "idiv rcx\n");
        fprintf(file, "push rax\n");
    }
}

static void equals_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    get_value(SECONDCHILD(root), file, global_vars);
    int offset = 0, type = 0;
    for(Table *current = global_vars->first; current; current = current->next)
        if(!strcmp(current->var.ident, FIRSTCHILD(FIRSTCHILD(root))->ident)){
            offset = current->var.deplct;
            type = current->var.is_int;
        }
    fprintf(file, "pop rax\n");
    if(type == INT)
        fprintf(file, "mov dword [global_vars + %d], eax\n", offset);
    else if(type == CHAR)
        fprintf(file, "mov byte [global_vars + %d], al\n", offset);
    else{
        fprintf(stderr, "Error line %d: unknown type\n", root->lineno);
        exit(SEMANTIC_ERROR);
    }
}

/**
 * @brief Writes the value of a node to a file as an assembly instruction.
 * @param root The node whose value is to be written.
 * @param file The file to write the assembly instruction to.
 * @return The value of the node.
 */
static void num_calc(Node *root, FILE * file){
    fprintf(file, "mov rax, %d\n", root->num);
    fprintf(file, "push rax\n");
}

static void ident_calc(Node *root, FILE * file, SymbolsTable *global_vars){
    int offset = 0, type;
    for(Table *current = global_vars->first; current; current = current->next){
        if(root->label == Array){
            if(!strcmp(current->var.ident, FIRSTCHILD(root)->ident)){
                offset = current->var.deplct + FIRSTCHILD(root)->num * (current->var.is_int ? 4 : 1);
                type = current->var.is_int;
            }
        }else {
            if(!strcmp(current->var.ident, root->ident)){
                offset = current->var.deplct;
                type = current->var.is_int;
            }
        }
    }
    if(type == INT){
        fprintf(file, "movsx rax, dword [global_vars + %d]\n", offset);
        fprintf(file, "push rax\n");
    }
    else if (type == CHAR){
        fprintf(file, "movsx rax, byte [global_vars + %d]\n", offset);
        fprintf(file, "push rax\n");
    }
    else{
        fprintf(stderr, "Error line %d: unknown type\n", root->lineno);
        exit(SEMANTIC_ERROR);
    }
}

static void character_calc(Node *root, FILE * file){
    fprintf(file, "mov rax, %d\n", root->ident[1]);
    fprintf(file, "push rax\n");
}

static void expression_calc(Node *root, FILE * file, SymbolsTable * global_vars){
    if(FIRSTCHILD(root)->label == Addsub || FIRSTCHILD(root)->label == Divstar)
        do_calc(FIRSTCHILD(root), file, global_vars);
    else
        get_value(FIRSTCHILD(root), file, global_vars);
}

static void function_calc(Node *root, FILE * file, SymbolsTable * global_vars){
    fprintf(file, ";Function %s\n", FIRSTCHILD(root)->ident);
    /*
    if(!strcmp(FIRSTCHILD(root)->ident, "getchar")){
        fprintf(file, "call _getchar\n");
        fprintf(file, "push rax\n");
    }
    else if(!strcmp(FIRSTCHILD(root)->ident, "getint")){
        fprintf(file, "call _getint\n");
        fprintf(file, "push rax\n");
    }
    else{
        fprintf(stderr, "Error line %d: unknown function\n", root->lineno);
        exit(SEMANTIC_ERROR);
    }*/
}

static void if_calc(Node *root, FILE *file, SymbolsTable *global_vars){
    //TO DOO
    /*get_value(FIRSTCHILD(root), file, global_vars);
    get_value(SECONDCHILD(root), file, global_vars);
    calc_to_asm(file);
    fprintf(file, "cmp rax, rcx\n");
    fprintf(file, "pop rcx\n");
    fprintf(file, "pop rax\n");
    switch(root->label){
        case Or:
            fprintf(file, "or rax, rcx\n");
            break;
        case And:
            fprintf(file, "and rax, rcx\n");
            break;
        case Eq:
            fprintf(file, "je ");
            break;
        case Order:
            if(!strcmp(root->ident, "<"))
                fprintf(file, "jl ");
            else if(!strcmp(root->ident, ">"))
                fprintf(file, "jg ");
            else if(!strcmp(root->ident, "<="))
                fprintf(file, "jle ");
            else if(!strcmp(root->ident, ">="))
                fprintf(file, "jge ");
            break;
        default:
            fprintf(stderr, "Error line %d: unknown type\n", root->lineno);
            exit(SEMANTIC_ERROR);
            break;
    }*/
}

void get_value(Node * root, FILE * file, SymbolsTable * global_vars){
    switch(root->label){
        case Variable:
            ident_calc(FIRSTCHILD(root), file, global_vars);
            break;
        case Num:
            num_calc(root, file);
            break;
        case Character:
            character_calc(root, file);
            break;
        case Expression:;
            expression_calc(root, file, global_vars);
            break;
        case Function:
            function_calc(root, file, global_vars);
            break;
        case If:
            if_calc(root, file, global_vars);
            break;
        default:
            fprintf(stderr, "Error line %d: unknown type\n", root->lineno);
            exit(SEMANTIC_ERROR);
            break;
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
            addsub_calc(root, file, global_vars);
            return 1;
        case Divstar:
            divstar_calc(root, file, global_vars);
            return 1;
        case Equals:
            equals_calc(root, file, global_vars);
            return -1;
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
        size += current->var.is_array ? current->var.size * (current->var.is_int ? 4 : 1) : (current->var.is_int ? 4 : 1);
    if(size > 0)
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
    fprintf(file, "section .text\n");
    fprintf(file, "_start:\n");
    in_depth_course(FIRSTCHILD(root), do_calc, NULL, NULL, global_vars, file);
    fprintf(file, "mov rax, 60\n");
    fprintf(file,  "mov rdi, 0\n");
    fprintf(file, "syscall\n");
    try(fclose(file));
}

int get_function_type(Node *root){
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
        printf("####################\n"); ///< Print a header for the table.
        printf("Identifier: %s\n", t->var.ident); ///< Print the identifier of the table.
        printf("Type: %s\n", t->var.is_int ? "int" : "char"); ///< Print the type of the table.
        printf("Array: %s\n", t->var.is_array ? "yes" : "no"); ///< Print if the table is an array.
        printf("Displacement: %d\n", t->var.deplct); ///< Print the displacement of the table.
        printf("Line number: %d\n", t->var.lineno); ///< Print the line number of the table.
        printf("\n"); ///< Print a newline character.
        print_table(t->next); ///< Print the next table in the symbol table.
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