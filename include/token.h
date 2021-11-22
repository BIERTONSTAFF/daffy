#ifndef DAF_TOKEN_H
#define DAF_TOKEN_H

typedef struct TOKEN_STRUCT {
    char* val;
    enum {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_LT,
        TOKEN_GT,
        TOKEN_ARROW_RIGHT,
        TOKEN_INT,
        TOKEN_SEMI,
        TOKEN_EOF
    } type;
} token_t;

token_t* init_token(char* val, int type);

const char* token_type_to_str(int type);

char* token_to_str(token_t* token);

#endif