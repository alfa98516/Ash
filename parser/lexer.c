#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
struct Lexer* initLexer(const int fd) {
    struct Lexer* lexer = (struct Lexer*)malloc(sizeof(struct Lexer));
    if (!lexer)
        return NULL;
    lexer->Tokens = initList();
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
    if (lexer->currentChar == EOF)
        return;
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
    if (!isalpha(lexer->currentChar))
        exit(3); // HACK: make an actual error handler.

    char* lexeme = malloc(MAX_ARG_NAME);

    int i = 0;                         // cry about it
    while ((isalpha(lexer->currentChar) ||
            isdigit(lexer->currentChar) &&
                (i < MAX_ARG_NAME))) { // need space for null terminator

        lexeme[i] = lexer->currentChar;
        i++;
        nextChar(lexer);
    }
    lexeme[i] = '\0';
    return lexeme;
}

void delLexer(struct Lexer* lexer) {
    struct Node* curr = lexer->Tokens->Head->next;
    while (curr) {
        if (curr->t.tokenId == WORD || curr->t.tokenId == ASSIGNMENT_WORD) {
            free(
                curr->t
                    .lexeme); // the lexeme of token type WORD is located on the heap.
        }
        curr = curr->next;
    }
    delList(lexer->Tokens);
    free(lexer);
}
