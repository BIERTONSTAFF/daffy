#include <stdlib.h>
#include "include/daf.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/asm_f.h"

void daf_compile(char* src) {
    lexer_t* lexer = init_lexer(src);
    parser_t* parser = init_parser(lexer);
    ast_t* root = parser_parse(parser);

    char* s = asm_f(root);

    printf("%s\n", s);
}

void daf_compile_file(const char* filename) {
 char* src = daf_read_file(filename);
 daf_compile(src);
 free(src);
}