#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "include/parser.h"
#include "include/types.h"

parser_t* init_parser(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}

token_t* parser_eat(parser_t* parser, int type) {
    if (parser->token->type != type) {
        printf("[PARSER] Unexpected token: '%s', was expecting: '%s'\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

    parser->token = lexer_next_token(parser->lexer);

    return parser->token;
}

ast_t* parser_parse(parser_t* parser) {
    return parser_parse_compound(parser);
}

ast_t* parser_parse_id(parser_t* parser) {
    char* val = calloc(strlen(parser->token->val) + 1, sizeof(char));
    strcpy(val, parser->token->val);
    parser_eat(parser, TOKEN_ID);

    if (parser->token->type == TOKEN_EQUALS) {
        parser_eat(parser, TOKEN_EQUALS);
        ast_t* ast = init_ast(AST_ASSIGNMENT);
        ast->name = val;
        ast->val = parser_parse_expr(parser);

        return ast;
    }

    ast_t* ast = init_ast(AST_VARIABLE);
    ast->name = val;

    if (parser->token->type == TOKEN_COLON) {
        parser_eat(parser, TOKEN_COLON);

        while (parser->token->type == TOKEN_ID) {
            ast->data_type = typename_to_int(parser->token->val);
            parser_eat(parser, TOKEN_ID);

            if (parser->token->type == TOKEN_LT) {
                parser_eat(parser, TOKEN_LT);
                ast->data_type += typename_to_int(parser->token->val);
                parser_eat(parser, TOKEN_ID);
                parser_eat(parser, TOKEN_GT);
            }
        }
    } else {
        if (parser->token->type == TOKEN_LPAREN) {
            ast->type = AST_CALL;
            ast->val = parser_parse_list(parser);
        }
    }

    return ast;
}

ast_t* parser_parse_block(parser_t* parser) {
    parser_eat(parser, TOKEN_LBRACE);

    ast_t* ast = init_ast(AST_COMPOUND);

    while (parser->token->type != TOKEN_RBRACE) {
        list_push(ast->children, parser_parse_expr(parser));
    }

    parser_eat(parser, TOKEN_RBRACE);

    return ast;
}

ast_t* parser_parse_list(parser_t* parser) {
    parser_eat(parser, TOKEN_LPAREN);
    ast_t* ast = init_ast(AST_COMPOUND);
    list_push(ast->children, parser_parse_expr(parser));

    while (parser->token->type == TOKEN_COMMA) {
        parser_eat(parser, TOKEN_COMMA);
        list_push(ast->children, parser_parse_expr(parser));
    }

    parser_eat(parser, TOKEN_RPAREN);

    if (parser->token->type == TOKEN_COLON) {
        parser_eat(parser, TOKEN_COLON);

        while (parser->token->type == TOKEN_ID) {
            ast->data_type = typename_to_int(parser->token->val);
            parser_eat(parser, TOKEN_ID);

            if (parser->token->type == TOKEN_LT) {
                parser_eat(parser, TOKEN_LT);
                ast->data_type += typename_to_int(parser->token->val);
                parser_eat(parser, TOKEN_ID);
                parser_eat(parser, TOKEN_GT);
            }
        }
    }

    if (parser->token->type == TOKEN_ARROW_RIGHT) {
        parser_eat(parser, TOKEN_ARROW_RIGHT);
        ast->type = AST_FUNCTION;
        ast->val = parser_parse_compound(parser);
    }

    return ast;
}

ast_t* parser_parse_int(parser_t* parser) {
    int int_value = atoi(parser->token->val);
    parser_eat(parser, TOKEN_INT);

    ast_t* ast = init_ast(AST_INT);
    ast->int_value = int_value;

    return ast;
}

ast_t* parser_parse_expr(parser_t* parser) {
    switch (parser->token->type) {
        case TOKEN_ID:
            return parser_parse_id(parser);
        case TOKEN_LPAREN:
            return parser_parse_list(parser);
        case TOKEN_INT:
            return parser_parse_int(parser);
        default: {
            printf("[PARSER] Unexpected token '%s'\n", token_to_str(parser->token));
            exit(1);
        }
    }
}

ast_t* parser_parse_compound(parser_t* parser) {
    unsigned int close = 0;

    if (parser->token->type == TOKEN_LBRACE) {
        parser_eat(parser, TOKEN_LBRACE);
        close = 1;
    }

    ast_t* compound = init_ast(AST_COMPOUND);

    while (parser->token->type != TOKEN_EOF && parser->token->type != TOKEN_RBRACE) {
        list_push(compound->children, parser_parse_expr(parser));

        if (parser->token->type == TOKEN_SEMI)
            parser_eat(parser, TOKEN_SEMI);
    }

    if (close)
        parser_eat(parser, TOKEN_RBRACE);

    return compound;
}