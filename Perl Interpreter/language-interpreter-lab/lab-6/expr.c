#include <math.h>
#include "expr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Create one node in an expression tree and return the structure.
*/

struct type *type_create(type_t kind, struct type *sub) {
  struct type *t = malloc(sizeof(*t));
  t->kind = kind;
  t->subtype = sub;
  return t;
}

struct decl *decl_create(struct expr *name, struct type *type,
                         struct expr *value, struct stmt *code,
                         struct decl *next) {
  struct decl *d = malloc(sizeof(*d));
  d->name = name->name;
  d->type = type;
  d->value = value;
  d->code = code;
  d->next = next;
  return d;
}

struct stmt *stmt_create(stmt_t kind, struct decl *decl, struct expr *init_expr,
                         struct expr *expr, struct expr *next_expr,
                         struct stmt *body, struct stmt *else_body,
                         struct stmt *next) {
  struct stmt *s = malloc(sizeof(*s));
  s->kind = kind;
  s->decl = decl;
  s->init_expr = init_expr;
  s->expr = expr;
  s->next_expr = next_expr;
  s->body = body;
  s->else_body = else_body;
  s->next = next;
  return s;
}

struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right) {
  /* Shortcut: sizeof(*e) means "the size of what e points to" */
  struct expr *e = malloc(sizeof(*e));

  e->kind = kind;
  e->left = left;
  e->right = right;
  e->name = "";
  e->integer_value = 0;
  e->float_value = 0.0;
  e->string_literal = "";

  return e;
}

struct expr *expr_create_name(const char *value) {
  struct expr *e = expr_create(EXPR_NAME, 0, 0);
  char *dest = malloc(sizeof(*value));
  strcpy(dest, value); // copy contents of source to dest
  e->name = dest;
  return e;
}

struct expr *expr_create_integer_literal(int value) {
  struct expr *e = expr_create(EXPR_INTEGER_LITERAL, 0, 0);
  e->integer_value = value;
  return e;
}

struct expr *expr_create_float_literal(float value) {
  struct expr *e = expr_create(EXPR_FLOAT_LITERAL, 0, 0);
  e->float_value = value;
  return e;
}

struct expr *expr_create_string_literal(const char *value) {
  struct expr *e = expr_create(EXPR_STRING_LITERAL, 0, 0);
  e->string_literal = value;
  return e;
}

/*
Recursively delete an expression tree.
*/

void expr_delete(struct expr *e) {
  /* Careful: Stop on null pointer. */
  if (!e)
    return;
  expr_delete(e->left);
  expr_delete(e->right);
  free(e);
}

void scope_bind(const char *name, struct expr *value) {
  if (symbol_table == NULL) {
    symbol_table = createSymbolMap();
  }
  insertSymbol(symbol_table, name, value);
}

struct expr *scope_lookup(const char *name) {
  return getSymbol(symbol_table, name);
}

/*
Recursively print an expression tree by performing an
in-order traversal of the tree, printing the current node
between the left and right nodes.
*/

void stmt_print(struct stmt *s) {
  if (!s)
    return;

  switch (s->kind) {
  case STMT_DECL:
    decl_print(s->decl);
    printf(";\n");
    break;
  case STMT_EXPR:
    expr_print(s->expr);
    break;
  case STMT_IF_ELSE:
    printf("if (");
    expr_print(s->expr);
    printf(") {\n");
    stmt_print(s->body);
    printf("\n}\n");
    break;
  case STMT_PRINT:
    printf("print ");
    expr_print(s->expr);
    printf(";\n");
    break;
  case STMT_BLOCK:
    stmt_print(s->body);
    break;
  }

  stmt_print(s->next);
}

void decl_print(struct decl *d) {
  printf("my ");
  printf("%s", d->name);
  printf(" = ");
  expr_print(d->value);
}

void expr_print(struct expr *e) {
  /* Careful: Stop on null pointer. */
  if (!e)
    return;

  printf("(");

  expr_print(e->left);

  switch (e->kind) {
  case EXPR_NAME:
    printf("'%s'", e->name);
    break;
  case EXPR_ADD:
    printf("+");
    break;
  case EXPR_SUBTRACT:
    printf("-");
    break;
  case EXPR_POW:
    printf("**");
    break;
  case EXPR_MULTIPLY:
    printf("*");
    break;
  case EXPR_DIVIDE:
    printf("/");
    break;
  case EXPR_INTEGER_LITERAL:
    printf("%d", e->integer_value);
    break;
  case EXPR_FLOAT_LITERAL:
    printf("%f", e->float_value);
    break;
  case EXPR_STRING_LITERAL:
    printf("%s", e->string_literal);
    break;
  }

  expr_print(e->right);
  printf(")");
}

/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/

void stmt_evaluate(struct stmt *s) {
  if (!s)
    return;

  switch (s->kind) {
  case STMT_DECL:
    decl_evaluate(s->decl);
    break;
  case STMT_EXPR:
    expr_evaluate(s->expr);
    break;
  case STMT_IF_ELSE:
    if (expr_evaluate(s->expr)) {
      stmt_evaluate(s->body);
    }
    break;
  case STMT_PRINT:
    // printf("%d", s->expr->kind);
    if (s->expr->kind == EXPR_STRING_LITERAL) {
      printf("%s", expr_string_evaluate(s->expr));
    } else if (s->expr->kind == EXPR_FLOAT_LITERAL) {
      printf("%f", expr_evaluate(s->expr));
    } else if (s->expr->kind == EXPR_INTEGER_LITERAL) {
      printf("%.0f", expr_evaluate(s->expr));
    } else if (s->expr->kind == EXPR_NAME) {
      printf("%.0f", expr_evaluate(s->expr));
    } else {
      printf("runtime error: print expression is not literal\n");
      exit(1);
    }
    break;
  case STMT_BLOCK:
    stmt_evaluate(s->body);
    break;
  }

  stmt_evaluate(s->next);
}

void decl_evaluate(struct decl *d) {
  if (!d)
    return;

  scope_bind(d->name, expr_create_float_literal(expr_evaluate((d->value))));
}

const char *expr_string_evaluate(struct expr *e) {
  /* Careful: Return zero on null pointer. */
  if (!e)
    return 0;

  switch (e->kind) {
  case EXPR_NAME:
  case EXPR_ADD:
  case EXPR_SUBTRACT:
  case EXPR_POW:
  case EXPR_MULTIPLY:
  case EXPR_DIVIDE:
  case EXPR_INTEGER_LITERAL:
  case EXPR_FLOAT_LITERAL:
    printf("runtime error: not a string expression\n");
    exit(1);
  case EXPR_STRING_LITERAL:
    return e->string_literal;
  }

  return "";
}

/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/

float expr_evaluate(struct expr *e) {
  /* Careful: Return zero on null pointer. */
  if (!e)
    return 0;

  float l = expr_evaluate(e->left);
  float r = expr_evaluate(e->right);

  switch (e->kind) {
  case EXPR_NAME:
    return expr_evaluate(scope_lookup(e->name));
  case EXPR_ADD:
    return l + r;
  case EXPR_SUBTRACT:
    return l - r;
  case EXPR_POW:
    return pow(l, r);
  case EXPR_MULTIPLY:
    return l * r;
  case EXPR_DIVIDE:
    if (r == 0) {
      printf("runtime error: divide by zero\n");
      exit(1);
    }
    return l / r;
  case EXPR_INTEGER_LITERAL:
    return e->integer_value;
  case EXPR_FLOAT_LITERAL:
    return e->float_value;
  case EXPR_STRING_LITERAL:
    printf("runtime error: string in expression\n");
    exit(1);
  }

  return 0;
}

void close_parser() { destroySymbolMap(symbol_table); }