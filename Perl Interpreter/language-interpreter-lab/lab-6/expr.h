/*
expr.h defines the structure of an expression node,
and the operations that can be performed upon it.
Note some things about this file that you should emulate:
- Every symbol in expr.[ch] begins with expr_.
- Use enumerations to define variant types.
- Build complex trees one node at a time.
- Define methods with recurse over those trees.
*/

#ifndef EXPR_H
#define EXPR_H

#include "symbol_map.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  EXPR_ADD,
  EXPR_SUBTRACT,
  EXPR_POW,
  EXPR_DIVIDE,
  EXPR_MULTIPLY,
  EXPR_NAME,
  EXPR_INTEGER_LITERAL,
  EXPR_FLOAT_LITERAL,
  EXPR_STRING_LITERAL
} expr_t;

struct expr {
  expr_t kind;
  struct expr *left;
  struct expr *right;
  const char *name;
  int integer_value;
  float float_value;
  const char *string_literal;
};

typedef enum { TYPE_INTEGER, TYPE_FLOAT, TYPE_STRING, TYPE_ARRAY } type_t;

struct type {
  type_t kind;
  struct type *subtype;
};

struct decl {
  const char *name;
  struct type *type;
  struct expr *value;
  struct stmt *code;
  struct decl *next;
};

typedef enum {
  STMT_DECL,
  STMT_EXPR,
  STMT_IF_ELSE,
  STMT_PRINT,
  STMT_BLOCK
} stmt_t;

struct stmt {
  stmt_t kind;
  struct decl *decl;
  struct expr *init_expr;
  struct expr *expr;
  struct expr *next_expr;
  struct stmt *body;
  struct stmt *else_body;
  struct stmt *next;
};


static struct SymbolMap *symbol_table = NULL;

struct decl *decl_create(struct expr *name, struct type *type,
                         struct expr *value, struct stmt *code,
                         struct decl *next);
struct stmt *stmt_create(stmt_t kind, struct decl *decl, struct expr *init_expr,
                         struct expr *expr, struct expr *next_expr,
                         struct stmt *body, struct stmt *else_body,
                         struct stmt *next);
struct expr *expr_create_name(const char *name);
struct expr *expr_create_integer_literal(int i);
struct expr *expr_create_float_literal(float f);
struct expr *expr_create_string_literal(const char *str);
struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right);
struct type *type_create(type_t kind, struct type *sub);

void scope_bind(const char *name, struct expr *sym);
struct expr *scope_lookup(const char *name);

void stmt_print(struct stmt *e);
void expr_print(struct expr *e);
void decl_print(struct decl *d);

void decl_evaluate(struct decl *e);
float expr_evaluate(struct expr *e);
const char * expr_string_evaluate(struct expr *e);
void stmt_evaluate(struct stmt *e);

void expr_delete(struct expr *e);
void close_parser();

#endif
