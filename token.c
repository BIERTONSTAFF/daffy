#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/token.h"

token_t* init_token(char* val, int type) {
    token_t* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->val = val;
    token->type = type;

    return token;
}

const char* token_type_to_str(int type) {
    switch (type) {
        case TOKEN_ID:
            return "TOKEN_ID";
        case TOKEN_EQUALS:
            return "TOKEN_EQUALS";
        case TOKEN_LPAREN:
            return "TOKEN_LPAREN";
        case TOKEN_RPAREN:
            return "TOKEN_RPAREN";
        case TOKEN_LBRACE:
            return "TOKEN_LBRACE";
        case TOKEN_RBRACE:
            return "TOKEN_RBRACE";
        case TOKEN_COLON:
            return "TOKEN_COLON";
        case TOKEN_COMMA:
            return "TOKEN_COMMA";
        case TOKEN_LT:
            return "TOKEN_LT";
        case TOKEN_GT:
            return "TOKEN_GT";
        case TOKEN_ARROW_RIGHT:
            return "TOKEN_ARROW_RIGHT";
        case TOKEN_INT:
            return "TOKEN_INT";
        case TOKEN_SEMI:
            return "TOKEN_SEMI";
        case TOKEN_EOF:
            return "TOKEN_EOF";
    }

    return "UNDEFINED";
}

char* token_to_str(token_t* token) {
    const char* type_str = token_type_to_str(token->type);
    const char* template = "<type='%s', int_type='%d', val='%s'>";

    char* str = calloc(strlen(type_str) + strlen(template) + 8, sizeof(char));
    sprintf(str, template, type_str, token->type, token->val);

    return str;
}