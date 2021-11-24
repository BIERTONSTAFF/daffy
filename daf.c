#include <stdlib.h>
#include <string.h>
#include "include/daf.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/asm_f.h"

static char* sh(const char* command) {
    char* out = (char*) calloc(1, sizeof(char));
    out[0] = '\0';

    FILE *fp;
    char path[1035];

    fp = popen(command, "r");

    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        out = (char*) realloc(out, (strlen(out) + strlen(path) + 1) * sizeof(char));
        strcat(out, path);
    }

    pclose(fp);

    return out;
}

void daf_compile(char* src) {
    lexer_t* lexer = init_lexer(src);
    parser_t* parser = init_parser(lexer);
    ast_t* root = parser_parse(parser);

    char* s = asm_f_root(root);

    daf_write_file("a.s", s);
    sh("C:/\"Program Files\"/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/as.exe a.s -o a.o");
    sh("C:/\"Program Files\"/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/ld.exe a.o -o a.out");
}

void daf_compile_file(const char* filename) {
 char* src = daf_read_file(filename);
 daf_compile(src);
 free(src);
}