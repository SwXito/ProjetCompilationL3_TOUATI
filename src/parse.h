#ifndef PROJET_PARSE_H
#define PROJET_PARSE_H

#include <string.h>
#include <getopt.h>
#include "compile.h"

void parse_args(int argc, char *argv[], Node * node, SymTabs *global_vars, SymTabs **decl_functions, int count);

#endif //PROJET_PARSE_H
