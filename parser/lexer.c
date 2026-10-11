#include "lexer.h"
#include "../macros.h"
#include "token.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lexer_error_handler(char* msg, struct Lexer* l) {
    fprintf(stderr, "%s: %d:%d\n", msg, l->line, l->col);
    delLexer(l);
    ASSERT(0);
}
int ident_called = 0;
struct Lexer* initLexer(const int fd) {
    struct Lexer* lexer = (struct Lexer*)malloc(sizeof(struct Lexer));
    if (!lexer) {
        fprintf(stderr, "Lexer heap allocation did not work.\n");
        ASSERT(0);
    }
    if (fd == -1) {
        lexer->f = stdin;
    } else {
        FILE* f = fdopen(fd, "r");
        if (f == NULL) {
            perror("Creating file pointer did not work\n");
        }
        lexer->f = f;
    }
    lexer->col = 0;
    lexer->line = 0;

    lexer->kw_hm = initHashMap();
    insertHm(lexer->kw_hm, "if\0", (struct _TOKEN){IF, "if\0"});
    insertHm(lexer->kw_hm, "then\0", (struct _TOKEN){THEN, "then\0"});
    insertHm(lexer->kw_hm, "else\0", (struct _TOKEN){ELSE, "else\0"});
    insertHm(lexer->kw_hm, "elif\0", (struct _TOKEN){ELIF, "elif\0"});
    insertHm(lexer->kw_hm, "fi\0", (struct _TOKEN){FI, "fi\0"});
    insertHm(lexer->kw_hm, "do\0", (struct _TOKEN){DO, "do\0"});
    insertHm(lexer->kw_hm, "done\0", (struct _TOKEN){DONE, "done\0"});
    insertHm(lexer->kw_hm, "case\0", (struct _TOKEN){CASE, "case\0"});
    insertHm(lexer->kw_hm, "esac\0", (struct _TOKEN){ESAC, "esac\0"});
    insertHm(lexer->kw_hm, "while\0", (struct _TOKEN){WHILE, "while\0"});
    insertHm(lexer->kw_hm, "until\0", (struct _TOKEN){UNTIL, "until\0"});
    insertHm(lexer->kw_hm, "for\0", (struct _TOKEN){FOR, "for\0"});
    insertHm(lexer->kw_hm, "in\0", (struct _TOKEN){IN, "in\0"});
    insertHm(lexer->kw_hm, "coproc\0", (struct _TOKEN){COPROC, "coproc\0"});
    insertHm(lexer->kw_hm, "time\0", (struct _TOKEN){TIME, "time\0"});
    insertHm(lexer->kw_hm, "select\0", (struct _TOKEN){SELECT, "select\0"});

    lexer->currentChar = getc(lexer->f);
    return lexer;
}

void nextChar(struct Lexer* lexer) {
    if (lexer->currentChar == EOF)
        return;
    lexer->currentChar = getc(lexer->f);
    if (lexer->currentChar == '\n') {
        lexer->col = -1;
        lexer->line++;
    }
    lexer->col++;
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
uint8_t* identifier(struct Lexer* lexer) {
    if (!isalpha(lexer->currentChar))
        lexer_error_handler(
            "Congrats, I have no idea how you managed to get this error.",
            lexer);
    uint8_t* lexeme = malloc(MAX_ARG_NAME);
    if (!lexeme) {
        lexer_error_handler("Identifier heap allocation did not work", lexer);
    }

    size_t i = 0;                // cry about it
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

uint8_t* string_builder(struct Lexer* lexer) {
    uint8_t* strng = malloc(MAX_ARG_NAME);
    size_t i = 0;
    int mode = 0; // 0 == "", 1 == ''
    if (lexer->currentChar == '\'') {
        mode = 1;
    }
    while (lexer->currentChar != '"' && lexer->currentChar != '\'') {
        if (lexer->currentChar == '\n') {
            lexer_error_handler("Strings cannot contain newline", lexer);
        }
        strng[i] = lexer->currentChar;
        i++;
        nextChar(lexer);
        if (i < MAX_ARG_NAME) {
            delLexer(lexer);
            lexer_error_handler("String was too big", lexer);
        }
    }
    strng[i] = '\0';
    return strng;
}

uint8_t* integer_builder(struct Lexer* lexer) {
    uint8_t* integer = malloc(MAX_DIGITS + 1); // +1 because nullterminator
    size_t i = 0;
    if (lexer->currentChar == '-') {
        integer[i] = '-';
        i++;
        nextChar(lexer);
    }
    while (isdigit(lexer->currentChar)) {
        if (MAX_DIGITS < i) {
            lexer_error_handler("Integer Overlfow.", lexer);
        }
        integer[i] = lexer->currentChar;
        nextChar(lexer);
        i++;
    }
    integer[i] = '\0';
    return integer;
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
    uint8_t* ident;
    size_t length;
    switch (lexer->currentChar) {
    case '&':
        setToken(lexer, AND, 1, (struct pair){'&', AND_IF});
        break;
    case '|':
        if (peekCharIs(lexer, '|')) {
            setToken(lexer, OR, 1, (struct pair){'|', OR_IF});
        } else {
            setToken(lexer, OR, 1, (struct pair){'&', OR_AND});
        }
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
        if (isdigit(peekChar(lexer))) {
            nextChar(lexer);
            uint8_t* integer = integer_builder(lexer);
            struct _TOKEN t = (struct _TOKEN){NUMBER, "\0"};
            memcpy(t.lexeme, integer, strlen((char*)integer) + 1);
            lexer->current = t;
            free(integer);
            break;
        }
        setToken(lexer, DASH, 1, (struct pair){'-', DECR});
        break;
    case '+':
        setToken(lexer, PLUS, 1, (struct pair){'+', INCR});
        break;
    case '*':
        setToken(lexer, MUL, 0);
        break;
    case '/':
        setToken(lexer, DIV, 0);
        break;
    case '(':
        setToken(lexer, LPAREN, 1, (struct pair){'(', LDPAREN});
        break;
    case ')':
        setToken(lexer, RPAREN, 1, (struct pair){')', RDPAREN});
        break;
    case '[':
        setToken(lexer, LBRACKET, 1, (struct pair){'[', LDBRACKET});
        break;
    case '{':
        setToken(lexer, LBRACE, 0);
        break;
    case '}':
        setToken(lexer, RBRACE, 0);
        break;
    case '!':
        setToken(lexer, BANG, 0);
        break;
    case '=':
        setToken(lexer, ASSIGN, 0);
        break;
    default:
        if (isalpha(lexer->currentChar)) {
            ident = identifier(lexer);
            Token t = findHm(lexer->kw_hm, ident);
            if (t.tokenId != ERROR) {
                lexer->current = t;
            } else {
                memset(lexer->current.lexeme, 0, 255);
                memcpy(lexer->current.lexeme, ident, strlen((char*)ident));
                if (lexer->currentChar == '=') {
                    lexer->current.lexeme[strlen((char*)ident)] = '=';
                    nextChar(lexer);

                    if (isalpha(peekChar(lexer))) {
                        size_t ident_len = strlen((char*)ident);
                        free(ident);
                        ident = identifier(lexer);
                        memcpy(lexer->current.lexeme + ident_len + 1, ident,
                               strlen((char*)ident) + 1);
                        lexer->current.tokenId = ASSIGNMENT_WORD;
                        free(ident);
                        break;
                    }
                } else if (peekCharIs(lexer, '"') || peekCharIs(lexer, '\'')) {
                    nextChar(lexer);
                }
                lexer->current.tokenId = WORD;
            }
            free(ident);
        } else if (isdigit(lexer->currentChar)) {
            uint8_t* integer = integer_builder(lexer);
            struct _TOKEN t = (struct _TOKEN){NUMBER, "\0"};
            memcpy(t.lexeme, integer, strlen((char*)integer) + 1);
            lexer->current = t;
            free(integer);
            break;
        }
    }
}

void delLexer(struct Lexer* lexer) {
    delMap(lexer->kw_hm);
    free(lexer);
}
