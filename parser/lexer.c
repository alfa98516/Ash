#include "lexer.h"
#include <stdlib.h>
struct Lexer* initLexer() {
    struct Lexer* lexer = (struct Lexer*)malloc(sizeof(struct Lexer));
    if (!lexer) return NULL;
}
