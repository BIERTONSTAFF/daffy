#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "include/asm_f.h"

char* asm_f_compound(ast_t* ast) {
    char* val = calloc(1, sizeof(char));

    for (int i = 0; i < (int)ast->children->size; i++) {
        ast_t* child_ast = (ast_t*) ast->children->items[i];
        char* next_val = asm_f(child_ast);
        val = realloc(val, (strlen(next_val) + 1) * sizeof(char));
        strcat(val, next_val);
    }

    return val;
}

char* asm_f_assignment(ast_t* ast) {

}

char* asm_f_variable(ast_t* ast) {

}

char* asm_f_call(ast_t* ast) {

}

char* asm_f_int(ast_t* ast) {

}

char* asm_f(ast_t* ast) {
    char* val = calloc(1, sizeof(char));
    char* next_val = 0;
    switch (ast->type) {
        case AST_COMPOUND:
            next_val = asm_f_compound(ast);
            break;
        case AST_ASSIGNMENT:
            next_val = asm_f_assignment(ast);
            break;
        case AST_VARIABLE:
            next_val = asm_f_variable(ast);
            break;
        case AST_CALL:
            next_val = asm_f_variable(ast);
            break;
        case AST_INT:
            next_val = asm_f_int(ast);
            break;
        default: {
            printf("[ASM_F] Not frontend for AST of type '%d'\n", ast->type);
            exit(1);
        }
        val = realloc(val, (strlen(next_val) + 1) * sizeof(char));
        strcat(val, next_val);

        return val;
    }
}