#include <stdlib.h>
#include "include/ast.h"

AST_T* init_ast(int type) {
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast-> type = type;

    return ast;
}