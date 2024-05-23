/**
 * @file compile.h
 * @brief Header file for compile functions.
 */

#ifndef __COMPILE__H
#define __COMPILE__H

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include "tree.h"
#include "build.h"
#include "../obj/tpcc.h"

#define EXIT_ERROR 3
#define SEMANTIC_ERROR 2
#define SYNTAX_ERROR 1
#define INT 1
#define CHAR 0
#define VOID -1
#define UNKNOWN -2

extern Node *node;

/**
 * @brief Structure representing an element in the symbol table.
 *
 * An element contains an identifier, a flag indicating if it's an integer,
 * and a displacement value.
 */
typedef struct elem{
    char *ident;  ///< Identifier of the element.
    int is_array; ///< Flag indicating if the element is an array.
    int size;     ///< Size of the array.
    int is_int;   ///< Flag indicating if the element is an integer.
    int deplct;   ///< Displacement of the element.
    int lineno;   ///< Line number of the element.
}Element;

/**
 * @brief Structure representing a table of symbols.
 *
 * A table contains an element and a pointer to the next table.
 */
typedef struct table{
    Element var;      ///< Element in the table.
    struct table *next; ///< Pointer to the next table.
}Table;

/**
 * @brief Structure representing a symbol table.
 *
 * A symbol table contains an offset and a pointer to the first table.
 */
typedef struct{
  int offset;       ///< Offset in the symbol table.
  Table* first;     ///< Pointer to the first table.
}SymTabs;

/**
 * @brief Structure representing a function symbol table.
 *
 * A function symbol table contains a table of parameters, a table of variables,
 * a name, a type, and a line number.
 */
typedef struct{
  Table* parameters;
  Table* variables;
  char *ident;
  int type;
  int lineno;
}SymTabsFct;

int count_functions(); ///< Function to count the number of functions in the tree.

int find_type_in_sb(char *var, SymTabs *table); ///< Function to find the type of a variable in the symbol table.

int find_type_in_fct(char *var_name, SymTabsFct *table); ///< Function to find the type of a variable in the function table.

int check_is_array(char *var_name, Table *table); ///< Function to check if a variable is an array.

SymTabs* creatSymbolsTable(); ///< Function to create a new symbol table.

SymTabsFct* creatSymbolsTableFct(char *ident, int type, int lineno); ///< Function to create a new function symbol table.

int check_in_table(SymTabs t, char *s); ///< Function to check_in_table if a symbol exists in the table.

int check_in_table_fct(Table* t, char *s); ///< Function to check if a symbol exists in the function table.

void fill_table_vars(SymTabs* t, Node *root); ///< Function to fill the table with variables.

void fill_table_fcts(SymTabsFct **t, SymTabs *global_vars, Node *root, int *nb_functions, char *filename); ///< Function to fill the table with functions.

SymTabs* fill_func_parameters_table(Node *root); ///< Function to fill the table with function parameters.

void fill_global_vars(SymTabs* t); ///< Function to fill the table with global variables.

SymTabsFct** fill_decl_functions(int nb_func, SymTabs *global_vars, char *filename); ///< Function to fill the table with declared functions.

void in_depth_course(Node * root, int (*calc)(Node *, FILE *, SymTabs *, SymTabsFct **, int, char *),
 void (*table)(SymTabs *, Node *), void (*check)(Node *), SymTabs *t, FILE * file, SymTabsFct **functions, int nb_functions, char *function_name); ///< Function to traverse the tree in depth.

void in_width_course(Node * root, void (*func)(SymTabs **, SymTabs *, Node *, int *), SymTabs **t, SymTabs *global_vars, int *nb_functions); ///< Function to traverse the tree in width.

void free_table(Table *t); ///< Function to free the memory allocated for the table.

void get_value(Node * root, FILE * file, SymTabs * global_vars, char *then_label,
 char *else_label, SymTabsFct **functions, int nb_functions, char *function_name); ///< Function to get the value of a node.

int do_calc(Node *root, FILE * file, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name); ///< Function to perform calculations on the tree nodes.

int expression_type(Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *function_name); ///< Function to get the type of an expression.

void free_symbols_table(SymTabs *t); ///< Function to free the memory allocated for the symbol table.

void free_tables(SymTabsFct** tables, int length); ///< Function to free the memory allocated for the tables.

void print_type(int type); ///< Function to print the type of a variable.

void find_types(Node *root, SymTabs *global_vars, SymTabs *functions); ///< Function to find the types of expressions in the program.

void print_table(Table *t); ///< Function to print the table.

void print_global_vars(SymTabs *t); ///< Function to print the global variables.

void print_functions(SymTabsFct **t, int nb_functions); ///< Function to print the declared functions.

int max(int a, int b); ///< Function to get the maximum of two integers.

int is_ident_array_in_table(char *ident, Table *table); ///< Function to check if an identifier is an array in the table.

void build_minimal_asm(FILE *file, Node *root, SymTabs *global_vars, SymTabsFct **functions, int nb_functions); ///< Function to build minimal assembly code from the tree.

int nb_params_function(SymTabsFct **functions, int nb_functions, char *function_name); ///< Function to get the number of parameters of a function.

int find_label_return(Node *root); ///< Function to find the label of a return statement.

int nb_vars_function(SymTabsFct **functions, int nb_functions, char *function_name); ///< Function to get the number of variables of a function.

int expression_result(Node *root); ///< Function to get the result of an expression.

void build_asm(SymTabs *global_vars, SymTabsFct **functions, int nb_functions, char *filename); ///< Function to build assembly code from the tree.

void build_global_vars_asm(SymTabs *t, char *filename); ///< Function to build assembly code for global variables.

#endif