/* tree.h */

#include <string.h>
#include <getopt.h>

typedef enum {
  Type, Void, If, Else, While, Return, Or, And,
  Character, Addsub, Divstar,
  Order, Eq,
  Ident,
  Num,
  Corps,
  Instructions,
  Prog,
  None,
  Function,
  Parameters,
  Equals,
  Array,
  Global_vars,
  Functions,
  Not,
  Variable,
  Expression
} label_t;

typedef struct Node {
  label_t label;
  struct Node *firstChild, *nextSibling;
  int lineno;
  int num;
  char * ident;
} Node;

Node *makeNode(label_t label);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
#define FOURTHCHILD(node) node->firstChild->nextSibling->nextSibling->nextSibling
