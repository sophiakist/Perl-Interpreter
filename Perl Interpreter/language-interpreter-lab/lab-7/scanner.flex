%{
#include "parser.h"
%}

%option nounput
%option noinput
%option noyywrap

DIGIT [0-9]
LETTER [a-zA-Z]
VAR [$][a-zA-Z]*
ARRAY [@][a-zA-Z_]*

%%
[ \n\r\t]*        ;
"#".*"\n"           /* comment */
(" "|\t|\n)         /* skip whitespace */
\".*\"              { return TOKEN_STRING; }
\:                  { return TOKEN_COLON; }
\#                  { return TOKEN_POUND; }
\\                  { return TOKEN_BACK; }
\"                  { return TOKEN_QUOTE; }
\!                  { return TOKEN_EXCLAIM; }
\;                  { return TOKEN_SEMI; }
\{                  { return TOKEN_OPEN_SQUIGGLE; }
\}                  { return TOKEN_CLOSE_SQUIGGLE; }
\(                  { return TOKEN_OPEN_PARENTHESIS; }
\)                  { return TOKEN_CLOSE_PARENTHESIS; }
\[                  { return TOKEN_OPEN_SQUARE; }
\]                  { return TOKEN_CLOSE_SQUARE; }
\,                  { return TOKEN_COMMA; }
\=                  { return TOKEN_EQUAL; }
\_                  { return TOKEN_UNDER; }
\?                  { return TOKEN_QUESTION; }
\.                  { return TOKEN_PERIOD; }
\/                  { return TOKEN_DIV; }
\+                  { return TOKEN_ADD; }
\-                  { return TOKEN_SUB; }
\*                  { return TOKEN_MULT; }
\**                 { return TOKEN_POW; }
\>                  { return TOKEN_GREATER_THAN; }
\<                  { return TOKEN_LESS_THAN; }
my                  { return TOKEN_MY; }
sub                 { return TOKEN_FUNCTION; }
print               { return TOKEN_PRINT; }
use                 { return TOKEN_USE; }
while               { return TOKEN_WHILE; }
do                  { return TOKEN_DO; }
for                 { return TOKEN_FOR; }
if                  { return TOKEN_IF; }
{ARRAY}             { return TOKEN_ARRAY; }
{VAR}               { return TOKEN_VAR; }
{LETTER}+           { return TOKEN_IDENT; }
{DIGIT}+            { return TOKEN_NUMBER; }
.                   { return TOKEN_ERROR; }
%%

/*
flex calls yywrap() whenever it reaches the end of the current file.
If yywrap returns false to indicate the end of the program.
It could alternatively open up another file and return true,
so that flex would keep going.
*/

