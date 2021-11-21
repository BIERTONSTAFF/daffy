#include <stdio.h>
#include <stdlib.h>
#include "include/parser.h"

parser_t* init_parser(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}

token_t* parser_in(parser_t* parser, int type) {
    if (parser->token->type != type) {
        printf("[PARSER] Unexpected token: '%s', was expecting: '%s'\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

    parser->token = lexer_next_token(parser->lexer);

    return parser->token;
}

AST_T* parser_parse(parser_t* parser) {
    return init_ast(AST_NOOP);
}

AST_T* parser_parse_compound(parser_t* parser) {
//    AST_T* compound = init_ast(AST_COMPOUND);
    while (parser->token->type != TOKEN_EOF) {
//        AST_T* child = */parser_parse(parser);
    }

    return init_ast(AST_NOOP);
}