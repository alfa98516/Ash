#include "parser/lexer.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd = open("/home/alfa/code/git/Ash/scripts/testing.sh", O_RDONLY);
    struct Lexer* lexer = initLexer(fd);
    while (!peekCharIs(lexer, EOF)) {
        nextToken(lexer);
        printf("%s\n", lexer->current.lexeme);
    }
    free(lexer);
}
