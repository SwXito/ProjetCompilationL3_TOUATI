#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "compile.h"

void check_decl(SymTabs *global_vars, SymTabs **decl_functions, int count, Node *root); ///< Function to check_in_table if a symbol exists in the table of declared functions.

void check_affectations(Node *root, SymTabs* global_vars, SymTabs **decl_functs, int count); ///< Function to check the affectations in the tree.

void semantic_check(SymTabs *global_vars, SymTabs **decl_functions, int count); ///< Function to perform semantic checks on the tree.

#endif