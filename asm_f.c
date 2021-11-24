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
    char* s = calloc(1, sizeof(char));
    if (ast->val->type = AST_FUNCTION) {
        const char* template = ".global %s\n"
                               "%s:\n";
        s = realloc(s, (strlen(template) + (strlen(ast->name) * 2) + 1) * sizeof(char));
        sprintf(s, template, ast->name, ast->name);

        ast_t* asm_val = ast->val;

        char* asm_val_val = asm_f(asm_val->val);

        s = realloc(s, (strlen(s) + strlen(asm_val_val) + 1) * sizeof(char));
        strcat(s, asm_val_val);
    }

    return s;
}

char* asm_f_variable(ast_t* ast) {

}

char* asm_f_call(ast_t* ast) {
    char* s = calloc(1, sizeof(char));
    if (strcmp(ast->name, "return") == 0) {
        ast_t* f_arg = (ast_t*) ast->val->children->size ? ast->val->children->items[0] : (void*) 0;
        const char* template = "mov $%d, %%eax\n"
                               "ret\n";
        char* ret_s = calloc(strlen(template) + 128, sizeof(char));
        sprintf(ret_s, template, f_arg ? f_arg->int_value : 0);
        s = realloc(s, (strlen(ret_s) + 1) * sizeof(char));
        strcat(s, ret_s);
    }

    return s;
}

char* asm_f_int(ast_t* ast) {

}

char* asm_f_root(ast_t* ast) {
    const char* section_text = ".section .text\n"
                               ".global _start\n"
                               "_start:\n"
                               "call main\n"
                               "mov \%eax, \%ebx\n"
                               "mov $1, \%eax\n"
                               "int $0x80\n\n";

    char* val = (char*) calloc((strlen(section_text) + 128), sizeof(char));
    strcpy(val, section_text);

    char* next_val = asm_f(ast);
    val = (char*) realloc(val, (strlen(val) + strlen(next_val) + 1) * sizeof(char));
    strcat(val, next_val);

    return val;
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
            next_val = asm_f_call(ast);
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