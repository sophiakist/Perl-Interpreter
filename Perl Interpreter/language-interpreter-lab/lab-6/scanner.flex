%{
#include "parser.h"
%}

%option nounput
%option noinput
%option noyywrap

DIGIT -?[0-9]*?[0-9]*?
LETTER [a-zA-Z]
VAR [$][a-zA-Z]*

%%
[ \n\r\t]*        ;
"#".*"\n"           /* comment */
(" "|\t|\n)         /* skip whitespace */
\".*\"              { return TOKEN_STRING; }
\;                  { return TOKEN_SEMI; }
\(                  { return TOKEN_OPEN_PARENTHESIS; }
\)                  { return TOKEN_CLOSE_PARENTHESIS; }
\=                  { return TOKEN_EQUAL; }
\/                  { return TOKEN_DIV; }
\+                  { return TOKEN_ADD; }
\-                  { return TOKEN_SUB; }
\*                  { return TOKEN_MULT; }
\**                 { return TOKEN_POW; }
my                  { return TOKEN_MY; }
print               { return TOKEN_PRINT; }
{VAR}+              { return TOKEN_VAR; }
{DIGIT}+            { return TOKEN_NUMBER; }
.                   { printf("scan error: bad token: %c\n",yytext[0]); }
%%

/*
flex calls yywrap() whenever it reaches the end of the current file.
If yywrap returns false to indicate the end of the program.
It could alternatively open up another file and return true,
so that flex would keep going.
*/

