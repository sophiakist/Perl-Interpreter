#include "token.h"
// https://github.com/sheredom/utest.h/blob/master/utest.h
#include "utest.h"
#include <stdio.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyrestart(FILE * input_file);
extern YY_BUFFER_STATE yy_scan_buffer(char *str, int i);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern FILE *yyin;
extern int yylex();
extern char *yytext;

UTEST_MAIN();

struct token_st {
  token_t t;
  char *p;
};

UTEST(scanner, identifier) {
  token_t t;
  // Must include the null character to terminate input
  char string[] = "\"Hello World\"\0"; 
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  ASSERT_EQ(TOKEN_STRING, (t = yylex()));
  ASSERT_STREQ("\"Hello World\"", yytext);

  ASSERT_EQ(TOKEN_EOF, (t = yylex()));
  ASSERT_STREQ("", yytext);

  yy_delete_buffer(buffer);
}

UTEST(scanner, assignment) {
  token_t t;
  // Must include the null character to terminate input
  char string[] = "=\0"; 
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  ASSERT_EQ(TOKEN_EQUAL, (t = yylex()));
  ASSERT_STREQ("=", yytext);

  ASSERT_EQ(TOKEN_EOF, (t = yylex()));
  ASSERT_STREQ("", yytext);

  yy_delete_buffer(buffer);
}

UTEST(scanner, hello_world) {
  struct token_st tokens[] = {
    {TOKEN_USE, "use"},
    {TOKEN_IDENT, "strict"},
    {TOKEN_SEMI, ";"},
    {TOKEN_USE, "use"},
    {TOKEN_IDENT, "warnings"},
    {TOKEN_SEMI, ";"},
    {TOKEN_PRINT, "print"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_STRING, "\"Hello World\""},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_SEMI, ";"},
    {TOKEN_EOF, ""}
  };

  yyin = fopen("samples/hello_world.pl", "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  int index = 0;
  token_t t;
  do {
    ASSERT_EQ(tokens[index].t, (t = yylex()));
    ASSERT_STREQ(tokens[index].p, yytext);
    ++index;
  } while (t != TOKEN_EOF);
}

UTEST(scanner, quadratic_function) {
  struct token_st tokens[] = {
    {TOKEN_USE, "use"},
    {TOKEN_IDENT, "strict"},
    {TOKEN_SEMI, ";"},
    {TOKEN_USE, "use"},
    {TOKEN_IDENT, "warnings"},
    {TOKEN_SEMI, ";"},
    {TOKEN_FUNCTION, "sub"},
    {TOKEN_IDENT, "quadratic"},
    {TOKEN_OPEN_SQUIGGLE, "{"},
    {TOKEN_IDENT, "my"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_VAR, "$a"},
    {TOKEN_COMMA, ","},
    {TOKEN_VAR, "$b"},
    {TOKEN_COMMA, ","},
    {TOKEN_VAR, "$c"},
    {TOKEN_COMMA, ","},
    {TOKEN_VAR, "$x"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_EQUAL, "="},
    {TOKEN_ARRAY, "@_"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$result"},
    {TOKEN_EQUAL, "="},
    {TOKEN_VAR, "$a"},
    {TOKEN_MULT, "*"},
    {TOKEN_VAR, "$x"},
    {TOKEN_POW, "**"},
    {TOKEN_NUMBER, "2"},
    {TOKEN_ADD, "+"},
    {TOKEN_VAR, "$b"},
    {TOKEN_MULT, "*"},
    {TOKEN_VAR, "$x"},
    {TOKEN_ADD, "+"},
    {TOKEN_VAR, "$c"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "return"},
    {TOKEN_VAR, "$result"},
    {TOKEN_SEMI, ";"},
    {TOKEN_CLOSE_SQUIGGLE, "}"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$a"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NUMBER, "2"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$b"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NUMBER, "-3"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$c"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NUMBER, "1"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$x"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NUMBER, "4"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$result"},
    {TOKEN_EQUAL, "="},
    {TOKEN_IDENT, "quadratic"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_VAR, "$a"},
    {TOKEN_COMMA, ","},
    {TOKEN_VAR, "$b"},
    {TOKEN_COMMA, ","},
    {TOKEN_VAR, "$c"},
    {TOKEN_COMMA, ","},
    {TOKEN_VAR, "$x"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_SEMI, ";"},
    {TOKEN_PRINT, "print"},
    {TOKEN_STRING, "\"Result for f($x) = $a*x^2 + $b*x + $c is: $result\""},
    {TOKEN_SEMI, ";"},
    {TOKEN_EOF, ""}
  };

  yyin = fopen("samples/quadratic_function.pl", "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  int index = 0;
  token_t t;
  do {
    ASSERT_EQ(tokens[index].t, (t = yylex()));
    ASSERT_STREQ(tokens[index].p, yytext);
    ++index;
  } while (t != TOKEN_EOF);
}

UTEST(scanner, sort_list) {
  struct token_st tokens[] = {
    {TOKEN_USE, "use"},
    {TOKEN_IDENT, "strict"},
    {TOKEN_SEMI, ";"},
    {TOKEN_USE, "use"},
    {TOKEN_IDENT, "warnings"},
    {TOKEN_SEMI, ";"},
    {TOKEN_FUNCTION, "sub"},
    {TOKEN_IDENT, "bubblesort"},
    {TOKEN_OPEN_SQUIGGLE, "{"},
    {TOKEN_IDENT, "my"},
    {TOKEN_ARRAY, "@array"},
    {TOKEN_EQUAL, "="},
    {TOKEN_ARRAY, "@_"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$n"},
    {TOKEN_EQUAL, "="},
    {TOKEN_ARRAY, "@array"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$swapped"},
    {TOKEN_SEMI, ";"},
    {TOKEN_DO, "do"},
    {TOKEN_OPEN_SQUIGGLE, "{"},
    {TOKEN_VAR, "$swapped"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NUMBER, "0"},
    {TOKEN_SEMI, ";"},   
    {TOKEN_FOR, "for"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$i"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_NUMBER, "1"},
    {TOKEN_PERIOD, "."},
    {TOKEN_PERIOD, "."},
    {TOKEN_VAR, "$n"},
    {TOKEN_SUB, "-"},
    {TOKEN_NUMBER, "1"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_OPEN_SQUIGGLE, "{"},
    {TOKEN_IF, "if"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_VAR, "$array"},
    {TOKEN_OPEN_SQUARE, "["},
    {TOKEN_VAR, "$i"},
    {TOKEN_SUB, "-"},
    {TOKEN_NUMBER, "1"},
    {TOKEN_CLOSE_SQUARE, "]"},
    {TOKEN_GREATER_THAN, ">"},
    {TOKEN_VAR, "$array"},
    {TOKEN_OPEN_SQUARE, "["},
    {TOKEN_VAR, "$i"},
    {TOKEN_CLOSE_SQUARE, "]"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_OPEN_SQUIGGLE, "{"},
    {TOKEN_IDENT, "my"},
    {TOKEN_VAR, "$temp"},
    {TOKEN_EQUAL, "="},
    {TOKEN_VAR, "$array"},
    {TOKEN_OPEN_SQUARE, "["},
    {TOKEN_VAR, "$i"},
    {TOKEN_SUB, "-"},
    {TOKEN_NUMBER, "1"},
    {TOKEN_CLOSE_SQUARE, "]"},
    {TOKEN_SEMI, ";"}, 
    {TOKEN_VAR, "$array"},
    {TOKEN_OPEN_SQUARE, "["},
    {TOKEN_VAR, "$i"},
    {TOKEN_SUB, "-"},
    {TOKEN_NUMBER, "1"},
    {TOKEN_CLOSE_SQUARE, "]"},
    {TOKEN_EQUAL, "="},
    {TOKEN_VAR, "$array"},
    {TOKEN_OPEN_SQUARE, "["},
    {TOKEN_VAR, "$i"},
    {TOKEN_CLOSE_SQUARE, "]"},
    {TOKEN_SEMI, ";"}, 
    {TOKEN_VAR, "$array"},
    {TOKEN_OPEN_SQUARE, "["},
    {TOKEN_VAR, "$i"},
    {TOKEN_CLOSE_SQUARE, "]"},
    {TOKEN_EQUAL, "="},
    {TOKEN_VAR, "$temp"},
    {TOKEN_SEMI, ";"},
    {TOKEN_VAR, "$swapped"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NUMBER, "1"},
    {TOKEN_SEMI, ";"},
    {TOKEN_CLOSE_SQUIGGLE, "}"},
    {TOKEN_CLOSE_SQUIGGLE, "}"},
    {TOKEN_CLOSE_SQUIGGLE, "}"},
    {TOKEN_WHILE, "while"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_VAR, "$swapped"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "return"},
    {TOKEN_ARRAY, "@array"},
    {TOKEN_SEMI, ";"},
    {TOKEN_CLOSE_SQUIGGLE, "}"},
    {TOKEN_IDENT, "my"},
    {TOKEN_ARRAY, "@unsorted"},
    {TOKEN_EQUAL, "="},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_NUMBER, "5"},
    {TOKEN_COMMA, ","},
    {TOKEN_NUMBER, "2"},
    {TOKEN_COMMA, ","},
    {TOKEN_NUMBER, "9"},
    {TOKEN_COMMA, ","},
    {TOKEN_NUMBER, "3"},
    {TOKEN_COMMA, ","},
    {TOKEN_NUMBER, "4"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_SEMI, ";"},
    {TOKEN_IDENT, "my"},
    {TOKEN_ARRAY, "@sorted"},
    {TOKEN_EQUAL, "="},
    {TOKEN_IDENT, "bubblesort"},
    {TOKEN_OPEN_PARENTHESIS, "("},
    {TOKEN_ARRAY, "@unsorted"},
    {TOKEN_CLOSE_PARENTHESIS, ")"},
    {TOKEN_SEMI, ";"},
    {TOKEN_PRINT, "print"},
    {TOKEN_STRING, "\"Unsorted array: @unsorted\""},
    {TOKEN_SEMI, ";"},
    {TOKEN_PRINT, "print"},
    {TOKEN_STRING, "\"Sorted array: @sorted\""},
    {TOKEN_SEMI, ";"},
    {TOKEN_EOF, ""}
  };

  yyin = fopen("samples/sort_list.pl", "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  int index = 0;
  token_t t;
  do {
    ASSERT_EQ(tokens[index].t, (t = yylex()));
    ASSERT_STREQ(tokens[index].p, yytext);
    ++index;
  } while (t != TOKEN_EOF);
}
