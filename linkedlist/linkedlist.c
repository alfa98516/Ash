#include "linkedlist.h"
#include "../parser/parser.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEmpty(struct LinkedList* LL) {
    return (LL->Head->next == LL->Tail);
}

struct LinkedList* initList(void) {
    struct LinkedList* LL =
        (struct LinkedList*)malloc(sizeof(struct LinkedList));
    if (!LL)
        return NULL;
    // initialize head and tail

    LL->Head = (struct Node*)malloc(sizeof(struct Node));
    LL->Tail = (struct Node*)malloc(sizeof(struct Node));

    if (!LL->Head || !LL->Tail) {
        free(LL);
        return NULL;
    }
    LL->Head->t = (Token){ERROR, "HEAD\0"};
    LL->Tail->t = (Token){ERROR, "TAIL\0"};
    LL->Head->next = LL->Tail;
    LL->Tail->next = NULL;

    return LL;
}

void prepend(struct LinkedList* LL, Token data) {

    // allocate memory for new Token
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->t = data;

    // prepend method adds to the front of the list
    newNode->next = LL->Head->next;
    LL->Head->next = newNode;
}

size_t length(struct LinkedList* LL) {
    struct Node* curr = LL->Head->next;
    size_t len = 0;
    while (curr != NULL) {
        if (curr == LL->Tail)
            return len;

        len++;
        curr = curr->next;
    }

    // the user could destroy the tail in some circumstances,
    // i don't know why they would do that but they could
    return len;
}

Token dequeue(struct LinkedList* LL) {
    Token t;

    if (isEmpty(LL))
        return (Token){ERROR, "EMPTY\0"};

    struct Node* oldNode = LL->Head->next;

    t = oldNode->t;

    LL->Head->next = oldNode->next;

    free(oldNode);
    return t;
}

void delList(struct LinkedList* LL) {
    if (!LL)
        return;
    struct Node* curr = LL->Head->next;
    struct Node* prev;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }

    free(LL->Head);
    free(LL);
}

Token find(struct LinkedList* LL, const uint8_t* t) {
    struct Node* curr = LL->Head->next;
    while (curr != NULL) {
        if (strcmp(curr->t.lexeme, (char*)t) == 0) {
            return curr->t;
        }
        curr = curr->next;
    }
    return (struct _TOKEN){ERROR, "ERROR\0"};
}
