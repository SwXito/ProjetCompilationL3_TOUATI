#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "compile.h"

void check_affectations(Node *root, SymTabs* global_vars, SymTabsFct **functions, int nb_functs, char *function_name); ///< Function to check the affectations in the tree.

void semantic_check(SymTabs *global_vars, SymTabsFct **functions, int nb_functions); ///< Function to perform semantic checks on the tree.

int expression_result(Node *root); ///< Function to get the result of an expression.

int nb_params_function(SymTabsFct **functions, int nb_functions, char *function_name);  ///< Function to get the number of parameters of a function.

#endif