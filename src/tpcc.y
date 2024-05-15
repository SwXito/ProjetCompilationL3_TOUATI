%{

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
int yylex(void);
void yyerror(char * msg);
extern int lineno;
extern int ch;
Node * node = NULL;

%}

%union{
    Node* node;
    int num;
    char ident[64];
}

%token <ident> TYPE VOID IF ELSE WHILE RETURN OR AND CHARACTER ADDSUB DIVSTAR IDENT ORDER EQ
%token <num> NUM

%type <node> DeclVars Prog Declarateurs DeclFonct DeclFoncts EnTeteFonct Parametres ListTypVar Corps SuiteInstr Instr 
%type <node> TB FB Exp M E T F LValue Arguments ListExp

%expect 1

%%

Prog:  DeclVars DeclFoncts {
    node = makeNode(Prog);
    Node * declV = makeNode(Global_vars);
    Node * declFuncs = makeNode(Functions);
    addChild(node, declV);
    addChild(declV, $1);
    addChild(node, declFuncs);
    addChild(declFuncs, $2);
    }
    ;
DeclVars:
       DeclVars TYPE Declarateurs ';' {
        if($1){
            $$ = $1;
            Node * tmp = makeNode(Type);
            tmp->ident = strdup($2);
            addChild(tmp, $3);
            addSibling($$, tmp);
        }
        else{
            $$ = makeNode(Type);
            $$->ident = strdup($2);
            addChild($$, $3);
        }
    }
    | {
        $$ = NULL;
        }
    ;
Declarateurs:
       Declarateurs ',' IDENT {
        $$ = $1;
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup($3);
        addSibling($$, tmp);
        }
    |  IDENT {
        $$ = makeNode(Ident);
        $$->ident = strdup($1);
        }
    |  Declarateurs ',' IDENT '[' NUM ']' {
        $$ = $1;
        Node *array = makeNode(Array);
        Node * tmp1 = makeNode(Ident);
        tmp1->ident = strdup($3);
        Node * num = makeNode(Num);
        num->num = $5;
        addChild(array, tmp1);
        addChild(tmp1, num);
        addSibling($$, array);
        }
    |  IDENT '[' NUM ']' {
        $$ = makeNode(Array);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup($1);
        addChild($$, tmp);
        Node * num = makeNode(Num);
        num->num = $3;
        addChild(tmp, num);
        } 
    ;
DeclFoncts:
       DeclFoncts DeclFonct {
        $$ = $1;
        addSibling($$, $2);
        }
    |  DeclFonct {
        $$ = $1;
        }
    ;
DeclFonct:
       EnTeteFonct Corps {
        $$ = makeNode(Function);
        addChild($$, $1);
        addChild($$, $2);
        }
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')' {
        $$ = makeNode(Type);
        $$->ident = strdup($1);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup($2);
        addSibling($$, tmp);
        Node *tmp2 = makeNode(Parameters);
        addSibling($$, tmp2);
        addChild(tmp2, $4);
        }
    |  VOID IDENT '(' Parametres ')' {
        $$ = makeNode(Void);
        $$->ident = strdup($1);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup($2);
        addSibling($$, tmp);
        Node *tmp2 = makeNode(Parameters);
        addSibling($$, tmp2);
        addChild(tmp2, $4);
        }
    ;
Parametres:
       VOID {
        $$ = makeNode(Void);
        }
    |  ListTypVar {
        $$ = $1;
        }
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT {
        $$ = $1; 
        Node * tmp1 = makeNode(Type); 
        tmp1->ident = strdup($3);
        Node * tmp2 = makeNode(Ident); 
        tmp2->ident = strdup($4);
        addChild(tmp1, tmp2); 
        addSibling($$, tmp1);
        }
    |  TYPE IDENT {
        $$ = makeNode(Type);
        $$->ident = strdup($1);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup($2);
        addChild($$, tmp);
        }
    |  ListTypVar ',' TYPE IDENT '[' ']' {
        $$ = $1;
        Node * arr = makeNode(Array);
        Node * tmp1 = makeNode(Type);
        tmp1->ident = strdup($3);
        Node * tmp2 = makeNode(Ident);
        tmp2->ident = strdup($4);
        addChild(tmp1, tmp2);
        addChild(arr, tmp1);
        addSibling($$, arr);
        }
    |  TYPE IDENT '[' ']' {
        $$ = makeNode(Array);
        Node * tmp1 = makeNode(Type);
        $$->ident = strdup($1);
        Node * tmp2 = makeNode(Ident);
        tmp2->ident = strdup($2);
        addChild(tmp1, tmp2);
        addChild($$, tmp1);
        }
    ;
Corps: '{' DeclVars SuiteInstr '}' {
    $$ = makeNode(Corps);
    addChild($$, $2);
    addChild($$, $3);
    }
    ;
SuiteInstr:
       SuiteInstr Instr {
        if($1){
            $$ = $1;
            addChild($$, $2);
            }
        else{
            $$ = makeNode(Instructions);
            addChild($$, $2);
            }
        }
    | {
        $$ = NULL;
        }
    ;
Instr:
       LValue '=' Exp ';' {
        $$ = makeNode(Equals);
        $$->ident = "=";
        addChild($$, $1);
        addChild($$, $3);
        }
    |  IF '(' Exp ')' Instr {
        $$ = makeNode(If);
        $$->ident = strdup($1);
        addChild($$, $3);
        addChild($$, $5);
        } 
    |  IF '(' Exp ')' Instr ELSE Instr {
        $$ = makeNode(If);
        $$->ident = strdup($1);
        addChild($$, $3);
        addChild($$, $5);
        addChild($$, $7);
        }
    |  WHILE '(' Exp ')' Instr {
        $$ = makeNode(While);
        $$->ident = strdup($1);
        addChild($$, $3);
        addChild($$, $5);
        }
    |  IDENT '(' Arguments  ')' ';' {
        $$ = makeNode(Function);
        Node * tmp = makeNode(Ident);
        Node * arg = makeNode(Parameters);
        tmp->ident = strdup($1);
        addChild(arg, $3);
        addChild(tmp, arg);
        addChild($$, tmp);
        }
    |  RETURN Exp ';' {
        $$ = makeNode(Return);
        $$->ident = strdup($1);
        addChild($$, $2);
        }
    |  RETURN ';' {
        $$ = makeNode(Return);
        $$->ident = strdup($1);
        }
    |  '{' SuiteInstr '}' {
        $$ = $2;
        }
    |  ';' {
        $$ = makeNode(None);
        }
    ;
Exp :  Exp OR TB {
    $$ = makeNode(Expression);
    Node * tmp = makeNode(Or);
    addChild($$, tmp);
    addChild(tmp, $1);
    addChild(tmp, $3);
    tmp->ident = strdup($2);
    }
    |  TB {
        $$ = makeNode(Expression);
        addChild($$, $1);
        }
    ;
TB  :  TB AND FB {
    $$ = makeNode(And);
    addChild($$, $1);
    addChild($$, $3);
    $$->ident = strdup($2);
    }
    |  FB {
        $$ = $1;
        }
    ;
FB  :  FB EQ M {
    $$ = makeNode(Eq);
    addChild($$, $1);
    addChild($$, $3);
    $$->ident = strdup($2);
    }
    |  M {
        $$ = $1;
        }
    ;
M   :  M ORDER E {
    $$ = makeNode(Order);
    addChild($$, $1);
    addChild($$, $3);
    $$->ident = strdup($2);
    }
    |  E {
        $$ = $1;
        }
    ;
E   :  E ADDSUB T {
    $$ = makeNode(Addsub);
    addChild($$, $1);
    addChild($$, $3);
    $$->ident = strdup($2);
    }
    |  T {
        $$ = $1;
        }
    ;    
T   :  T DIVSTAR F {
    $$ = makeNode(Divstar);
    addChild($$, $1);
    addChild($$, $3);
    $$->ident = strdup($2);
    }
    |  F {
        $$ = $1;
        }
    ;
F   :  ADDSUB F {
        $$ = makeNode(Addsub);
        addChild($$, $2);
        $$->ident = strdup($1);
        }
    |  '!' F {
        $$ = makeNode(Not);
        addChild($$, $2);
        }
    |  '(' Exp ')' {
        $$ = $2;
        }
    |  NUM {
        $$ = makeNode(Num);
        $$->num = $1;
        }
    |  CHARACTER {
        $$ = makeNode(Character);
        $$->ident = strdup($1);
        }
    |  LValue {
        $$ = $1;
        }
    |  IDENT '(' Arguments  ')' {
        $$ = makeNode(Function);
        Node * tmp = makeNode(Ident);
        Node * arg = makeNode(Parameters);
        tmp->ident = strdup($1);
        addChild(arg, $3);
        addChild(tmp, arg);
        addChild($$, tmp);
        }
    ;
LValue:
       IDENT {
        $$ = makeNode(Variable);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup($1);
        addChild($$, tmp);
        }
    |  IDENT '[' Exp ']' {
        $$ = makeNode(Variable);
        Node * tmp = makeNode(Array);
        addChild($$, tmp);
        Node * tmp2 = makeNode(Ident);
        tmp2->ident = strdup($1);
        addChild(tmp, tmp2);
        addChild(tmp2, $3);
        }
    ;
Arguments:
       ListExp {
        $$ = $1;
        }
    | {
        $$ = makeNode(Void);
        }
    ;
ListExp:
       ListExp ',' Exp {
        $$ = $1;
        addSibling($$, $3);
        }
    |  Exp {
        $$ = $1;
        }
    ;
%%

void yyerror(char * s){
    fprintf(stderr, "%s : line %d, col %d\n", s, lineno, ch);
    exit(1);
}