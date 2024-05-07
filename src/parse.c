//
// Created by dams on 21/04/24.
//

#include "parse.h"

static void help(){
    printf("Usage: ./bin/tpcas [OPTIONS] < filename\n");
    printf("Analyze and execute TPC programs.\n\n");
    printf("For automatic tests.\n");
    printf("Use command : ./tests.sh\n");
    printf("You can also make your own test\n");
    printf("Type a tpc program after using command: ./tpcas\n\n");
    printf("Options:\n");
    printf(" -h --help      Display this help message\n");
    printf(" -t --tree      Display the abstract syntax tree\n");
    printf("\n");
}

void parse_args(int argc, char *argv[], Node * node, SymTabs *global_vars, SymTabs **decl_functions, int count){
    int show_help = 0, show_tree = 0, show_tables = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || (strcmp(argv[i], "-h") == 0))
            show_help = 1;
        else if (strcmp(argv[i], "--tree") == 0 || (strcmp(argv[i], "-t") == 0))
            show_tree = 1;
        else if (strcmp(argv[i], "--symtabs") == 0 || (strcmp(argv[i], "-s") == 0))
            show_tables = 1;
        else
            fprintf(stderr, "Unknown option or argument: %s\n", argv[i]);
    }
    if (show_tree)
        printTree(node);
    if (show_help)
        help();
    if(show_tables){
        print_global_vars(global_vars);
        printf("----------------------------------\n");
        print_decl_functions(decl_functions, count);
    }
}