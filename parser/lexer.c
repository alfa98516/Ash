#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        memcpy(lexer->current.lexeme, "EOI\0", 4);
        return;
    }

    size_t length;
    switch (lexer->currentChar) {
    case '&':
        setToken(lexer, AND, 1, (struct pair){'&', AND_IF});
        break;
    case '|':
        setToken(lexer, OR, 1, (struct pair){'|', OR_IF});
        break;
    case ';':
        if (peekCharIs(lexer, ';')) {
            setToken(lexer, SEMI, 1, (struct pair){';', DSEMI});
        } else {
            setToken(lexer, SEMI, 0);
        }
        break;
    case '<':
        lexer->current.tokenId = LESS;
        memcpy(lexer->current.lexeme, "<\0", 2);
        length = 1;
        nextChar(lexer);
        if (lexer->currentChar == '<') {
            lexer->current.tokenId = DLESS;
            memcpy(lexer->current.lexeme + length, "<\0", 2);
            length++;
            nextChar(lexer);
            if (lexer->currentChar == '<') {
                lexer->current.tokenId = TLESS;
                memcpy(lexer->current.lexeme + length, "<\0", 2);
                length++;
            } else if (lexer->currentChar == '-') {
                lexer->current.tokenId = DLESSDASH;
                memcpy(lexer->current.lexeme + length, "-\0", 2);
                length++;
            }
        } else if (lexer->currentChar == '>') {
            lexer->current.tokenId = LESSGREAT;
            memcpy(lexer->current.lexeme + length, ">\0", 2);
            length++;
        } else if (lexer->currentChar == '&') {
            lexer->current.tokenId = LESSAND;
            memcpy(lexer->current.lexeme + length, "&\0", 2);
            length++;
        }
        nextChar(lexer);
        break;
    case '>':
        if (peekCharIs(lexer, '>')) {
            setToken(lexer, GREAT, 1, (struct pair){'>', DGREAT});
        } else if (peekCharIs(lexer, '&')) {
            setToken(lexer, GREAT, 1, (struct pair){'&', GREATAND});
        } else {
            setToken(lexer, GREAT, 1, (struct pair){'|', CLOBBER});
        }
        break;
    case '-':
        setToken(lexer, DASH, 1, (struct pair){'-', DECR});
    case '+':
        setToken(lexer, PLUS, 1, (struct pair){'+', INCR});
        break;
    case '*':
        setToken(lexer, MUL, 0);
        break;
    case '/':
        setToken(lexer, DIV, 0);
    }
}

void delLexer(struct Lexer* lexer) { free(lexer); }
