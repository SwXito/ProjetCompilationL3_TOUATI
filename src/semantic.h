#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "compile.h"

void check_affectations(Node *root, SymTabs* global_vars, SymTabs **decl_functs, int count, SymTabs *functions); ///< Function to check the affectations in the tree.

void semantic_check(SymTabs *global_vars, SymTabs **decl_functions, int count, SymTabs *functions); ///< Function to perform semantic checks on the tree.

int expression_result(Node *root); ///< Function to get the result of an expression.

#endif