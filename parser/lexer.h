#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER
#include "../linkedlist/linkedlist.h"
#include "token.h"
#include <stdio.h>
#define MAX_TOK                                                                \
    2048 // gargantuan amount of tokens probably.
         // Worst case MAX_ARG_NAME * MAX_TOK = 522,240 bytes = 5 Mb
         // of memory for the tokens.
struct Lexer {
    char currentChar;
    struct Node* current; // will be used in the parser
    struct LinkedList*
        Tokens; // actual pointer to the linked list, we fill this with our tokens
    FILE* f;
};
struct Lexer* initLexer(int fd);
void nextChar(struct Lexer* lexer);
void nextToken(struct Lexer* lexer);
char peekChar(struct Lexer* lexer);
int peekCharIs(struct Lexer* lexer, char c);
char* identifier(struct Lexer* lexer);
void setToken(
    struct Lexer* lexer, TokenId Ti,
    TokenId*
        tokenIDs); // probably not gonna make this function. (not yet at least)
void delLexer(struct Lexer* lexer);
#endif
