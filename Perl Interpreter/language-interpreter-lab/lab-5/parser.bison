%{
#include <stdio.h>
%}

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
    char* string_val;
    int int_val;
}

%type <string_val> TOKEN_STRING
%type <int_val> TOKEN_NUMBER TOKEN_INT

%start program
%%

program:
    statements

statements: statement
    | statements statement
    

statement: use_statement
    | print_statement
    | assignment
    | do_statement
    | for_statement
    | if_statement
    

expr: type TOKEN_MULT factor
    | type TOKEN_DIV factor
    | type TOKEN_SUB factor
    | type TOKEN_PERIOD TOKEN_PERIOD expr
    | TOKEN_VAR index
    | factor
    ;
      

type: TOKEN_ARRAY
    | TOKEN_VAR
    | TOKEN_NUMBER
    | TOKEN_STRING
    

use_statement: TOKEN_USE TOKEN_IDENT TOKEN_SEMI

do_statement: TOKEN_DO TOKEN_OPEN_SQUIGGLE statements TOKEN_CLOSE_SQUIGGLE TOKEN_WHILE TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS

for_statement: TOKEN_FOR TOKEN_MY TOKEN_VAR TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS TOKEN_OPEN_SQUIGGLE statements TOKEN_CLOSE_SQUIGGLE

if_statement: TOKEN_IF conditional TOKEN_OPEN_SQUIGGLE statements TOKEN_CLOSE_SQUIGGLE

conditional: TOKEN_OPEN_PARENTHESIS TOKEN_VAR index TOKEN_GREATER_THAN TOKEN_VAR index TOKEN_CLOSE_PARENTHESIS

index: TOKEN_OPEN_SQUARE expr TOKEN_CLOSE_SQUARE

print_statement: TOKEN_PRINT TOKEN_OPEN_PARENTHESIS TOKEN_STRING TOKEN_CLOSE_PARENTHESIS TOKEN_SEMI

assignment: TOKEN_MY expr TOKEN_EQUAL expr TOKEN_SEMI
          | TOKEN_MY TOKEN_VAR TOKEN_SEMI
          | TOKEN_VAR TOKEN_EQUAL expr TOKEN_SEMI
          | TOKEN_VAR index TOKEN_EQUAL TOKEN_VAR index TOKEN_SEMI
          | TOKEN_VAR index TOKEN_EQUAL TOKEN_VAR TOKEN_SEMI

factor: type TOKEN_ADD expr
    | TOKEN_SUB expr
    | type_array
    | power 
    | type

type_array: TOKEN_OPEN_PARENTHESIS array_parameters TOKEN_CLOSE_PARENTHESIS

array_parameters: array_parameters TOKEN_COMMA type
                | type

power: type TOKEN_POW expr

%%

int yyerror(char *s) {
    printf("parse error: %s\n", s);
    return 1;
}
