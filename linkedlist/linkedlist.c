#include "linkedlist.h"
#include "../parser/parser.h"

#include <stdlib.h>

int isEmpty(struct LinkedList* LL) {
    return (LL->Head->next == LL->Tail);
}

struct LinkedList* init(void) {
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

void del(struct LinkedList* LL) {
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
