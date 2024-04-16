%{

#include "tree.h"
#include "tpcas.h"

int lineno = 1;
int ch = 1;
%}

%option nounput
%option noinput


%x COMMENT

%%

"/*"   { BEGIN COMMENT; }
<COMMENT>. { ch += yyleng; }
<COMMENT>\n        { ch = 0; lineno++; }
<COMMENT>"*/"   { BEGIN INITIAL;}


"while" {ch+= yyleng; strcpy(yylval.ident, yytext); return WHILE;}
"if" {ch+= yyleng; strcpy(yylval.ident, yytext); return IF;}
"else" {ch+= yyleng; strcpy(yylval.ident, yytext); return ELSE;}
"void" {ch+= yyleng; strcpy(yylval.ident, yytext); return VOID;}
"return" {ch+= yyleng; strcpy(yylval.ident, yytext); return RETURN;}

"int" {ch+= yyleng; strcpy(yylval.ident, yytext); return TYPE;}
"char" {ch+= yyleng; strcpy(yylval.ident, yytext); return TYPE;}

[0-9]+ {ch+= yyleng; yylval.num = atoi(yytext); return NUM;}

'[^']' {ch+= yyleng; strcpy(yylval.ident, yytext); return CHARACTER;}
'\\n' {ch+= yyleng; strcpy(yylval.ident, yytext); return CHARACTER;}
'\\t' {ch+= yyleng; strcpy(yylval.ident, yytext); return CHARACTER;}
'\'' {ch+= yyleng; strcpy(yylval.ident, yytext); return CHARACTER;}

[A-Za-z_][A-Za-z0-9_]* {ch+= yyleng; strcpy(yylval.ident, yytext); return IDENT; }

"==" {ch+= yyleng; strcpy(yylval.ident, yytext); return EQ;}
"!=" {ch+= yyleng; strcpy(yylval.ident, yytext); return EQ;}

"<" {ch+= yyleng; strcpy(yylval.ident, yytext); return ORDER;}
"<=" {ch+= yyleng; strcpy(yylval.ident, yytext); return ORDER;}
">" {ch+= yyleng; strcpy(yylval.ident, yytext); return ORDER;}
">=" {ch+= yyleng; strcpy(yylval.ident, yytext); return ORDER;}

"+" {ch+= yyleng; strcpy(yylval.ident, yytext); return ADDSUB;}
"-" {ch+= yyleng; strcpy(yylval.ident, yytext); return ADDSUB;}

"/" {ch+= yyleng; strcpy(yylval.ident, yytext); return DIVSTAR;}
"*" {ch+= yyleng; strcpy(yylval.ident, yytext); return DIVSTAR;}
"%" {ch+= yyleng; strcpy(yylval.ident, yytext); return DIVSTAR;}

"||" {ch+= yyleng; strcpy(yylval.ident, yytext); return OR;}
"&&" {ch+= yyleng; strcpy(yylval.ident, yytext); return AND;}

"=" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
";" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"," {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
")" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"]" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"[" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"(" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"{" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"}" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}
"!" {ch+= yyleng; strcpy(yylval.ident, yytext); return yytext[0];}

"//".* {lineno++;}

[ \t]+ {ch += yyleng; }

\n  { ch = 0; lineno++; }

.  { return 1; }


%%
