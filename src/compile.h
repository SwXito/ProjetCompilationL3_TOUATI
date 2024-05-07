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
#include "../obj/tpcas.h"

#define EXIT_ERROR 3
#define SEMANTIC_ERROR 2
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
}SymbolsTable;

int count_functions(); ///< Function to count the number of functions in the tree.

int find_type_in_sb(char *var, SymbolsTable *table); ///< Function to find the type of a variable in the symbol table.

SymbolsTable* creatSymbolsTable(); ///< Function to create a new symbol table.

int check_in_table(SymbolsTable t, char *s); ///< Function to check_in_table if a symbol exists in the table.

void fill_table_vars(SymbolsTable* t, Node *root); ///< Function to fill the table with variables.

void fill_table_fcts(SymbolsTable **t, SymbolsTable *global_vars, Node *root, int *nb_functions); ///< Function to fill the table with functions.

SymbolsTable* fill_func_parameters_table(Node *root); ///< Function to fill the table with function parameters.

void fill_global_vars(SymbolsTable* t); ///< Function to fill the table with global variables.

SymbolsTable** fill_decl_functions(int nb_func, SymbolsTable *global_vars); ///< Function to fill the table with declared functions.

void in_depth_course(Node * root, int (*calc)(Node *, FILE *, SymbolsTable *), void (*table)(SymbolsTable *, Node *), void (*check)(Node *), SymbolsTable *t, FILE * file); ///< Function to traverse the tree in depth.

void in_width_course(Node * root, void (*func)(SymbolsTable **, SymbolsTable *, Node *, int *), SymbolsTable **t, SymbolsTable *global_vars, int *nb_functions); ///< Function to traverse the tree in width.

void free_table(Table *t); ///< Function to free the memory allocated for the table.

void get_value(Node * root, FILE * file, SymbolsTable * global_vars); ///< Function to get the value of a node.

int do_calc(Node *root, FILE * file, SymbolsTable *global_vars); ///< Function to perform calculations on the tree nodes.

int expression_type(Node *root); ///< Function to get the type of an expression.

int get_function_type(Node *root); ///< Function to get the type of a function.

void free_symbols_table(SymbolsTable *t); ///< Function to free the memory allocated for the symbol table.

void free_tables(SymbolsTable **tables, int length); ///< Function to free the memory allocated for the tables.

void print_type(int type);

void find_types(Node *root);

void print_table(Table *t); ///< Function to print the table.

void print_global_vars(SymbolsTable *t); ///< Function to print the global variables.

void print_decl_functions(SymbolsTable **t, int count); ///< Function to print the declared functions.

void build_minimal_asm(Node *root, SymbolsTable *global_vars); ///< Function to build minimal assembly code from the tree.

void build_global_vars_asm(SymbolsTable *t); ///< Function to build assembly code for global variables.

#endif