#include "../parser/lexer.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd = open("/home/alfa/code/git/Ash/scripts/testing.sh", O_RDONLY);
    struct Lexer* lexer = initLexer(fd);

    while (lexer->current.tokenId != EOI) {
        nextToken(lexer);
        printf("{lexeme: '%s', TokenID: ", lexer->current.lexeme);
        switch (lexer->current.tokenId) {
        case ERROR:
            printf("ERROR");
            break;
        case EOI:
            printf("EOI");
            break;
        case WORD:
            printf("WORD");
            break;
        case ASSIGNMENT_WORD:
            printf("ASSIGNMENT_WORD");
            break;
        case NUMBER:
            printf("NUMBER");
            break;
        case IO_NUMBER:
            printf("IO_NUMBER");
            break;
        case AND:
            printf("AND");
            break;
        case AND_IF:
            printf("AND_IF");
            break;
        case OR_IF:
            printf("OR_IF");
            break;
        case OR:
            printf("OR");
            break;
        case SEMI:
            printf("SEMI");
            break;
        case DSEMI:
            printf("DSEMI");
            break;
        case LESS:
            printf("LESS");
            break;
        case DLESS:
            printf("DLESS");
            break;
        case TLESS:
            printf("TLESS");
            break;
        case GREAT:
            printf("GREAT");
            break;
        case DGREAT:
            printf("DGREAT");
            break;
        case LESSAND:
            printf("LESSAND");
            break;
        case GREATAND:
            printf("GREATAND");
            break;
        case LESSGREAT:
            printf("LESSGREAT");
            break;
        case DLESSDASH:
            printf("DLESSDASH");
            break;
        case CLOBBER:
            printf("CLOBBER");
            break;
        case DASH:
            printf("DASH");
            break;
        case DECR:
            printf("DECR");
            break;
        case PLUS:
            printf("PLUS");
            break;
        case INCR:
            printf("INCR");
            break;
        case MUL:
            printf("MUL");
            break;
        case DIV:
            printf("DIV");
            break;
        case IF:
            printf("IF");
            break;
        case THEN:
            printf("THEN");
            break;
        case ELSE:
            printf("ELSE");
            break;
        case ELIF:
            printf("ELIF");
            break;
        case FI:
            printf("FI");
            break;
        case DO:
            printf("DO");
            break;
        case DONE:
            printf("DONE");
            break;
        case CASE:
            printf("CASE");
            break;
        case ESAC:
            printf("ESAC");
            break;
        case UNTIL:
            printf("UNTIL");
            break;
        case FOR:
            printf("FOR");
            break;
        case LPAREN:
            printf("LPAREN");
            break;
        case LDPAREN:
            printf("LDPAREN");
            break;
        case RPAREN:
            printf("RPAREN");
            break;
        case RDPAREN:
            printf("RDPAREN");
            break;
        case LBRACKET:
            printf("LBRACKET");
            break;
        case RBRACKET:
            printf("RBRACKET");
            break;
        case LDBRACKET:
            printf("LDBRACKET");
            break;
        case RDBRACKET:
            printf("RDBRACKET");
            break;
        case LBRACE:
            printf("LBRACE");
            break;
        case RBRACE:
            printf("RBRACE");
            break;
        case BANG:
            printf("BANG");
            break;
        case IN:
            printf("IN");
            break;
        case WHILE:
            printf("WHILE");
            break;
        case TIME:
            printf("TIME");
            break;
        case COPROC:
            printf("COPROC");
            break;
        case STRING_LITERAL:
            printf("STRING_LITERAL");
            break;
        case OR_AND:
            printf("OR_AND");
            break;
        case SELECT:
            printf("SELECT");
            break;
        }
        printf("}\n");
    }

    delLexer(lexer);
}
