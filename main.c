#include <stdio.h>
#include "include/daf.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please specify input file.\n");
        return 1;
    }

    daf_compile_file(argv[1]);

    return 0;
}