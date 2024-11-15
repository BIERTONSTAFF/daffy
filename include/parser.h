#ifndef DAF_PARSER_H
#define DAF_PARSER_H
#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* token;
} parser_t;

parser_t* init_parser(lexer_t* lexer);

token_t* parser_eat(parser_t* parser, int type);

ast_t* parser_parse(parser_t* parser);

ast_t* parser_parse_expr(parser_t* parser);

ast_t* parser_parse_list(parser_t* parser);

ast_t* parser_parse_compound(parser_t* parser);

#endif
