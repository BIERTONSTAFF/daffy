#ifndef DAF_PARSER_H
#define DAF_PARSER_H
#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* token;
} parser_t;

parser_t* init_parser(lexer_t* lexer);

token_t* parser_in(parser_t* parser, int type);

AST_T* parser_parse(parser_t* parser);

AST_T* parser_parse_compound(parser_t* parser);

#endif
