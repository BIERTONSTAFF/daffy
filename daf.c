#include <stdlib.h>
#include "include/daf.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"

void daf_compile(char* src) {
    lexer_t* lexer = init_lexer(src);
    parser_t* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    token_t* token = 0;

    while ((token = lexer_next_token(lexer))->type != TOKEN_EOF) {
        printf("%s\n", token_to_str(token));
    }
};

void daf_compile_file(const char* filename) {
 char* src = daf_read_file(filename);
 daf_compile(src);
 free(src);
};