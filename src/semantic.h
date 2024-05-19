#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "compile.h"

void check_affectations(Node *root, SymTabs* global_vars, SymTabsFct **functions, int nb_functs, char *function_name); ///< Function to check the affectations in the tree.

void semantic_check(SymTabs *global_vars, SymTabsFct **functions, int nb_functions); ///< Function to perform semantic checks on the tree.

#endif