#include "parser/lexer.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd = open("/home/alfa/code/git/Ash/scripts/testing.sh", O_RDONLY);
    struct Lexer* lexer = initLexer(fd);
    char* id = identifier(lexer);
    printf("%s\n", id);
    nextChar(lexer);
    char* id2 = identifier(lexer);
    printf("%s\n", id2);
    free(id);
    free(id2);
    delLexer(lexer);
}
