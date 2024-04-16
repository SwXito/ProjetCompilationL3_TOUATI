/* tree.c */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
extern int lineno;

static const char *StringFromLabel[] = {
  "Type", "Void", "If", "Else", "While", "Return", "||", "&&",
  "Character", "Addsub", "Divstar",
  "Order", "=",
  "Ident",
  "Num",
  "Corps",
  "instructions",
  "Prog",
  "None",
  "Function",
  "Parameters",
  ":=",
  "array",
  "global_vars",
  "Functions",
  "!",
  "Variable"
};

Node *makeNode(label_t label) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    printf("Run out of memory\n");
    exit(1);
  }
  node->label = label;
  node-> firstChild = node->nextSibling = NULL;
  node->lineno=lineno;
  node->ident = NULL;
  return node;
}

void addSibling(Node *node, Node *sibling) {
  Node *curr = node;
  while (curr->nextSibling != NULL) {
    curr = curr->nextSibling;
  }
  curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
  if (parent->firstChild == NULL) {
    parent->firstChild = child;
  }
  else {
    addSibling(parent->firstChild, child);
  }
}

void deleteTree(Node *node) {
    /*if(node->ident)
        free(node->ident);*/
    if (node->firstChild) {
        deleteTree(node->firstChild);
    }
    if (node->nextSibling) {
        deleteTree(node->nextSibling);
    }
    free(node);
}

void printTree(Node *node) {
  static bool rightmost[128]; // tells if node is rightmost sibling
  static int depth = 0;       // depth of current node
  for (int i = 1; i < depth; i++) { // 2502 = vertical line
    printf(rightmost[i] ? "    " : "\u2502   ");
  }
  if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
    printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
  }

  if(node->ident != NULL)
    printf("%s", node->ident);
  else if(node->label == Num)
    printf("%d", node->num);
  else
    printf("%s", StringFromLabel[node->label]);
  printf("\n");
  
  depth++;
  for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
    rightmost[depth] = (child->nextSibling) ? false : true;
    printTree(child);
  }
  depth--;
}

void parse_args(int argc, char *argv[], Node * node){
  int show_tree = 0;
  int show_help = 0;
  for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || (strcmp(argv[i], "-h") == 0)) {
            show_help = 1;
        } else if (strcmp(argv[i], "--tree") == 0 || (strcmp(argv[i], "-t") == 0)){
            show_tree = 1;
        } else {
            fprintf(stderr, "Unknown option or argument: %s\n", argv[i]);
        }
  }
  if (show_tree) {
    printTree(node);
  }
  if (show_help) {
    help();
  }
}

void help(){
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
