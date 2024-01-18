
/*
Declare token types at the top of the bison file,
causing them to be automatically generated in parser.tab.h
for use by scanner.c.
*/

%debug
%define parse.error detailed

%token TOKEN_INT
%token TOKEN_WHILE
%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MULT
%token TOKEN_POW
%token TOKEN_GREATER_THAN
%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_IF
%token TOKEN_IDENT
%token TOKEN_NUMBER
%token TOKEN_ERROR
%token TOKEN_UNDER
%token TOKEN_QUESTION
%token TOKEN_PRINT 
%token TOKEN_USE
%token TOKEN_PERIOD
%token TOKEN_DIV
%token TOKEN_LESS_THAN
%token TOKEN_VAR
%token TOKEN_EQUAL
%token TOKEN_MY
%token TOKEN_COMMA
%token TOKEN_CLOSE_PARENTHESIS
%token TOKEN_OPEN_PARENTHESIS
%token TOKEN_CLOSE_SQUIGGLE
%token TOKEN_OPEN_SQUIGGLE
%token TOKEN_SEMI
%token TOKEN_EXCLAIM
%token TOKEN_POUND
%token TOKEN_ARRAY
%token TOKEN_OPEN_SQUARE
%token TOKEN_CLOSE_SQUARE
%token TOKEN_QUOTE
%token TOKEN_BACK
%token TOKEN_COLON
%token TOKEN_STRING
%token TOKEN_FUNCTION

%union {
  struct stmt *stmt;
  struct expr *expr;
  struct decl *decl;
};

%type <stmt> program statements statement print_statement assignment if_statement block while_statement for_statement
%type <expr> expr term factor name sum array_subscript star_expr
%type <decl> declaration

%{
#define YYDEBUG 1

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "expr.h"


/*
Clunky: Manually declare the interface to the scanner generated by flex. 
*/

extern int yylineno;
extern char *yytext;
extern int yylex();
extern void yyerror(const char*);

/*
Clunky: Keep the final result of the parse in a global variable,
so that it can be retrieved by main().
*/

struct stmt * parser_result = 0;

%}


%%

program:
    statements { parser_result = $1; return 0; }
    ;

statements: statement { $$ = $1; }
    | statement statements { $$ = $1; $1->next = $2; }
    ;

block: statement { $$ = $1; }
    | statement block { $$ = $1; $1->next = $2; }
    ;

statement: print_statement TOKEN_SEMI { $$ = $1; }
    | assignment TOKEN_SEMI { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | for_statement { $$ = $1; }
    ;

assignment: declaration { $$ = stmt_create(STMT_DECL,$1,0,0,0,0,0,0); }
    ;

print_statement: TOKEN_PRINT name { $$ = stmt_create(STMT_PRINT,0,0,$2,0,0,0,0); }
    ;

if_statement : TOKEN_IF expr TOKEN_OPEN_SQUIGGLE block TOKEN_CLOSE_SQUIGGLE { $$ = stmt_create(STMT_IF,0,0,$2,0,$4,0,0); }
    ;

while_statement : TOKEN_WHILE expr TOKEN_OPEN_SQUIGGLE block TOKEN_CLOSE_SQUIGGLE { $$ = stmt_create(STMT_WHILE ,0,0,$2,0,$4,0,0); }
    ;

for_statement : TOKEN_FOR expr TOKEN_OPEN_SQUIGGLE block TOKEN_CLOSE_SQUIGGLE { $$ = stmt_create(STMT_FOR,0,0,$2,0,$4,0,0); }
    ;

declaration: TOKEN_MY name TOKEN_EQUAL expr { $$ = decl_create($2,type_create(TYPE_FLOAT,0),$4,0,0); }
    | array_subscript TOKEN_EQUAL expr
    { $$ = decl_create($1,0,$3,0,0); }
    | name TOKEN_EQUAL expr { $$ = decl_create($1,type_create(TYPE_FLOAT,0),$3,0,0); }
    ;

name : TOKEN_VAR { $$ = expr_create_name(yytext); }
    | TOKEN_ARRAY { $$ = expr_create_name(yytext); }
    | TOKEN_STRING { $$ = expr_create_string_literal(yytext); }
    ;

array_subscript : name TOKEN_OPEN_SQUARE expr TOKEN_CLOSE_SQUARE { $$ = expr_create(EXPR_SUBSCRIPT,$1,$3); }
    ;
    
star_expr :  expr 
    { $$ = expr_create(EXPR_ARRAY,$1,0); }
  | expr TOKEN_COMMA star_expr
    { $$ = expr_create(EXPR_ARRAY,$1,$3); }
    ;

expr : sum TOKEN_GREATER_THAN sum
    { $$ = expr_create(EXPR_GREATER_THAN,$1,$3); }
  | sum
    { $$ = $1; }
    ;

sum : sum TOKEN_ADD term { $$ = expr_create(EXPR_ADD,$1,$3); }
    | sum TOKEN_SUB term { $$ = expr_create(EXPR_SUBTRACT,$1,$3); }
    | term { $$ = $1; }
    ;
    
term: term TOKEN_MULT factor { $$ = expr_create(EXPR_MULTIPLY,$1,$3); }
    | term TOKEN_DIV factor { $$ = expr_create(EXPR_DIVIDE,$1,$3); }
    | factor { $$ = $1; }
    ;

factor : factor TOKEN_POW factor { $$ = expr_create(EXPR_POW,$1,$3); }
    | TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS { $$ = $2; }
    | TOKEN_SUB factor { $$ = expr_create(EXPR_SUBTRACT, expr_create_integer_literal(0),$2); }
    | TOKEN_NUMBER
    { $$ = expr_create_integer_literal(atoi(yytext)); }
    | TOKEN_OPEN_PARENTHESIS star_expr TOKEN_CLOSE_PARENTHESIS
    { $$ = $2; }
    | TOKEN_MY TOKEN_VAR expr { $$ = $3; }
    | TOKEN_NUMBER TOKEN_PERIOD TOKEN_PERIOD name { $$ = $4; }
    | array_subscript
    { $$ = $1; }
    | name { $$ = $1; }
    ;
%%

void yyerror(const char* msg) {
    fprintf(stderr, "Error | Line: %d\n%s\n",yylineno,msg);
}