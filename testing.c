#include "linkedlist/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct LinkedList* ll = init();
    Token testToken1 = {.tokenId = ERROR, .lexeme = "HELLO1\0"};
    Token testToken2 = {.tokenId = ERROR, .lexeme = "HELLO2\0"};
    Token testToken3 = {.tokenId = ERROR, .lexeme = "HELLO3\0"};
    Token testToken4 = {.tokenId = ERROR, .lexeme = "HELLO4\0"};
    prepend(ll, testToken1);
    prepend(ll, testToken2);
    prepend(ll, testToken3);
    prepend(ll, testToken4);
    Token retToken1 = dequeue(ll);
    printf("%s\n", retToken1.lexeme);
    Token retToken2 = dequeue(ll);
    printf("%s\n", retToken2.lexeme);
    Token retToken3 = dequeue(ll);
    printf("%s\n", retToken3.lexeme);
    Token retToken4 = dequeue(ll);
    printf("%s\n", retToken4.lexeme);
    del(ll);
}
