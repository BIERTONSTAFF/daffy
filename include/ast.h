#ifndef DAF_AST_H
#define DAF_AST_H
#include "list.h"

typedef struct AST_STRUCT {
    enum {
        AST_COMPOUND,
        AST_FUNCTION,
        AST_CALL,
        AST_ASSIGNMENT,
        AST_DEFINITION_TYPE,
        AST_VARIABLE,
        AST_STATEMENT,
        AST_INT,
        AST_NOOP
    } type;
    list_t* children;
    char* name;
    struct AST_STRUCT* val;
    int int_value;
    int data_type;
} ast_t;

ast_t* init_ast(int type);

#endif
