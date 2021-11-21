#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/lexer.h"
#include "include/macros.h"

lexer_t* init_lexer(char* src) {
    lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return lexer;
}

void lexer_advance(lexer_t* lexer) {
    if (lexer->i < lexer->src_size && lexer->c != '\0') {
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}

char lexer_peek(lexer_t* lexer, int offset) {
    return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

token_t* lexer_advance_with(lexer_t* lexer, token_t* token) {
    lexer_advance(lexer);
    return token;
}

token_t* lexer_advance_current(lexer_t* lexer, int type) {
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    token_t* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

void lexer_skip_whitespace(lexer_t* lexer) {
    while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
        lexer_advance(lexer);
}

token_t* lexer_parse_id(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    while (isalpha(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){ lexer->c, 0 });
        lexer_advance(lexer);
    };

    return init_token(value, TOKEN_ID);
};

token_t* lexer_parse_number(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    while (isdigit(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){ lexer->c, 0 });
        lexer_advance(lexer);
    };

    return init_token(value, TOKEN_INT);
};

token_t* lexer_next_token(lexer_t* lexer) {
    while (lexer->c != '\0') {
        lexer_skip_whitespace(lexer);
        if (isalnum(lexer->c))
            return lexer_advance_with(lexer, lexer_parse_id(lexer));

        if (isdigit(lexer->c))
            return lexer_advance_with(lexer, lexer_parse_number(lexer));

        switch (lexer->c) {
            case '=': {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token("=>", TOKEN_ARROW_RIGHT));
                return lexer_advance_with(lexer, init_token("=", TOKEN_EQUALS));
            }
            case '(':
                return lexer_advance_current(lexer, TOKEN_LPAREN);
            case ')':
                return lexer_advance_current(lexer, TOKEN_RPAREN);
            case '{':
                return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}':
                return lexer_advance_current(lexer, TOKEN_RBRACE);
            case ':':
                return lexer_advance_current(lexer, TOKEN_COLON);
            case ',':
                return lexer_advance_current(lexer, TOKEN_COMMA);
            case '<':
                return lexer_advance_current(lexer, TOKEN_LT);
            case '>':
                return lexer_advance_current(lexer, TOKEN_GT);
            case ';':
                return lexer_advance_current(lexer, TOKEN_SEMI);
            case '\0': break;
            default: {
                printf("[LEXER] Unexpected character '%s'\n", lexer->c);
                exit(1);
            }
        }
    }

    return init_token(0, TOKEN_EOF);
};