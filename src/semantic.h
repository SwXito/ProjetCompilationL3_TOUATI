#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "compile.h"

void semantic_check(SymbolsTable *global_vars, SymbolsTable **decl_functions, int count); ///< Function to perform semantic checks on the tree.

#endif