#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER
#include "../hashmap/hashmap.h"
#include "token.h"
#include <stdarg.h>
#include <stdio.h>
#define MAX_TOK                                                                                    \
    2048 // gargantuan amount of tokens probably.
         // Worst case MAX_ARG_NAME * MAX_TOK = 522,240 bytes = 5 Mb
         // of memory for the tokens.
struct Lexer {
    char currentChar;
    Token current; // will be used in the parser
    FILE* f;
    struct HashMap* kw_hm;
};

struct pair {
    char c;
    TokenId id;
};

struct Lexer* initLexer(int fd);
void nextChar(struct Lexer* lexer);
void nextToken(struct Lexer* lexer);
char peekChar(struct Lexer* lexer);
int peekCharIs(struct Lexer* lexer, char c);
uint8_t* identifier(struct Lexer* lexer);
uint8_t* integer_builder(struct Lexer* lexer);
uint8_t* string_builder(struct Lexer* lexer);
int whiteSpace(struct Lexer* lexer);
void setToken(struct Lexer* lexer, TokenId Ti, int nPairs,
              ...); // probably not gonna make this function. (not yet at least)
void delLexer(struct Lexer* lexer);
#endif
