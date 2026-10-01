#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
struct Lexer* initLexer(const int fd) {
    struct Lexer* lexer = (struct Lexer*)malloc(sizeof(struct Lexer));
    if (!lexer) return NULL;
    if (fd == -1) {
        lexer->f = stdin;
    } else {
        FILE* f = fdopen(fd, "r");
        if (f == NULL) {
            perror("Creating file pointer did not work\n");
        }
        lexer->f = f;
    }
    lexer->currentChar = getc(lexer->f);
    return lexer;
}

void nextChar(struct Lexer* lexer) {
    if (lexer->currentChar == EOF) return;
    lexer->currentChar = getc(lexer->f);
}

char peekChar(struct Lexer* lexer) {
    char c = getc(lexer->f);
    ungetc(c, lexer->f);
    return c;
}

int peekCharIs(struct Lexer* lexer, char c) {
    if (peekChar(lexer) == c) {
        return 1;
    }
    return 0;
}

/*
 * @brief: All of the form [a-zA-Z][a-zA-Z0-9]*
 */
char* identifier(struct Lexer* lexer) {
    if (!isalpha(lexer->currentChar)) exit(3); // HACK: make an actual error handler.

    char* lexeme = malloc(MAX_ARG_NAME);

    int i = 0; // cry about it
    while ((isalpha(lexer->currentChar) || isdigit(lexer->currentChar)) &&
           (i < MAX_ARG_NAME)) { // need space for null terminator

        lexeme[i] = lexer->currentChar;
        i++;
        nextChar(lexer);
    }
    lexeme[i] = '\0';
    return lexeme;
}

int whiteSpace(struct Lexer* lexer) {
    int n = 0;
    while (isspace(lexer->currentChar) && lexer->currentChar != EOF) {
        n++;
        nextChar(lexer);
    }
    return n > 0;
}

void setToken(struct Lexer* lexer, TokenId Ti, int nPairs, ...) {
    va_list pairs;
    va_start(pairs, nPairs);
    char nextC = peekChar(lexer);
    struct pair p = va_arg(pairs, struct pair);
    if (nPairs == 0 || (nPairs > 0 && (p.c != nextC))) {
        struct _TOKEN tok = {.tokenId = Ti};
        tok.lexeme[0] = lexer->currentChar;
        tok.lexeme[1] = '\0';
        lexer->current = tok;
        nextChar(lexer);
    } else if (lexer->currentChar != EOF) {
        char startChar = lexer->currentChar;
        nextChar(lexer);
        struct _TOKEN tok = {.tokenId = Ti};
        tok.lexeme[0] = startChar;
        for (int i = 0; i < nPairs; i++) {
            if (lexer->currentChar == p.c) {
                tok.tokenId = p.id;
                tok.lexeme[i + 1] = p.c;
                tok.lexeme[i + 2] = '\0';
                lexer->current = tok;
                nextChar(lexer);
            }
        }
    }
}

void nextToken(struct Lexer* lexer) {
    while (whiteSpace(lexer))
        ;
    while (lexer->currentChar == '#') {
        while (lexer->currentChar != '\n') {
            nextChar(lexer);
        }
        nextChar(lexer);
    }

    while (whiteSpace(lexer))
        ;

    if (lexer->currentChar == EOF) {
        setToken(lexer, EOI, 0);
        return;
    }

    switch (lexer->currentChar) {
    case '&':
        if (peekCharIs(lexer, '&')) {
            setToken(lexer, AND, 1, (struct pair){'&', AND_IF});
        } else {
            setToken(lexer, AND, 0);
        }
        break;
    case '+':
        if (peekCharIs(lexer, '+')) {
            setToken(lexer, PLUS, 1, (struct pair){'+', INCR});
        } else {
            setToken(lexer, PLUS, 0);
        }
        break;
    case '-':
    }
}

void delLexer(struct Lexer* lexer) { free(lexer); }
