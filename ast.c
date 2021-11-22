#include <stdlib.h>
#include "include/ast.h"

ast_t* init_ast(int type) {
    ast_t* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast-> type = type;

    if (type == AST_COMPOUND)
        ast->children = init_list(sizeof(struct AST_STRUCT*));
    return ast;
}