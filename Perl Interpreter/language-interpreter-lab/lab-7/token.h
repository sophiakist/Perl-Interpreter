/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_TOKEN_H_INCLUDED
# define YY_YY_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_INT = 258,               /* TOKEN_INT  */
    TOKEN_WHILE = 259,             /* TOKEN_WHILE  */
    TOKEN_ADD = 260,               /* TOKEN_ADD  */
    TOKEN_SUB = 261,               /* TOKEN_SUB  */
    TOKEN_MULT = 262,              /* TOKEN_MULT  */
    TOKEN_POW = 263,               /* TOKEN_POW  */
    TOKEN_GREATER_THAN = 264,      /* TOKEN_GREATER_THAN  */
    TOKEN_DO = 265,                /* TOKEN_DO  */
    TOKEN_FOR = 266,               /* TOKEN_FOR  */
    TOKEN_IF = 267,                /* TOKEN_IF  */
    TOKEN_IDENT = 268,             /* TOKEN_IDENT  */
    TOKEN_NUMBER = 269,            /* TOKEN_NUMBER  */
    TOKEN_ERROR = 270,             /* TOKEN_ERROR  */
    TOKEN_UNDER = 271,             /* TOKEN_UNDER  */
    TOKEN_QUESTION = 272,          /* TOKEN_QUESTION  */
    TOKEN_PRINT = 273,             /* TOKEN_PRINT  */
    TOKEN_USE = 274,               /* TOKEN_USE  */
    TOKEN_PERIOD = 275,            /* TOKEN_PERIOD  */
    TOKEN_DIV = 276,               /* TOKEN_DIV  */
    TOKEN_LESS_THAN = 277,         /* TOKEN_LESS_THAN  */
    TOKEN_VAR = 278,               /* TOKEN_VAR  */
    TOKEN_EQUAL = 279,             /* TOKEN_EQUAL  */
    TOKEN_MY = 280,                /* TOKEN_MY  */
    TOKEN_COMMA = 281,             /* TOKEN_COMMA  */
    TOKEN_CLOSE_PARENTHESIS = 282, /* TOKEN_CLOSE_PARENTHESIS  */
    TOKEN_OPEN_PARENTHESIS = 283,  /* TOKEN_OPEN_PARENTHESIS  */
    TOKEN_CLOSE_SQUIGGLE = 284,    /* TOKEN_CLOSE_SQUIGGLE  */
    TOKEN_OPEN_SQUIGGLE = 285,     /* TOKEN_OPEN_SQUIGGLE  */
    TOKEN_SEMI = 286,              /* TOKEN_SEMI  */
    TOKEN_EXCLAIM = 287,           /* TOKEN_EXCLAIM  */
    TOKEN_POUND = 288,             /* TOKEN_POUND  */
    TOKEN_ARRAY = 289,             /* TOKEN_ARRAY  */
    TOKEN_OPEN_SQUARE = 290,       /* TOKEN_OPEN_SQUARE  */
    TOKEN_CLOSE_SQUARE = 291,      /* TOKEN_CLOSE_SQUARE  */
    TOKEN_QUOTE = 292,             /* TOKEN_QUOTE  */
    TOKEN_BACK = 293,              /* TOKEN_BACK  */
    TOKEN_COLON = 294,             /* TOKEN_COLON  */
    TOKEN_STRING = 295,            /* TOKEN_STRING  */
    TOKEN_FUNCTION = 296           /* TOKEN_FUNCTION  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 51 "parser.bison"

  struct stmt *stmt;
  struct expr *expr;
  struct decl *decl;

#line 111 "token.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TOKEN_H_INCLUDED  */
