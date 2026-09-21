#ifndef LINKED_LIST
#define LINKED_LIST
#include "token.h"
struct Node {
    Token t;
    struct Node* next;
};

struct LinkedList {
    struct Node* Head;
    struct Node* Tail;
};

struct LinkedList* init();
int isEmpty(struct LinkedList* LL);
void prepend(struct LinkedList* LL, Token data);
Token dequeue(struct LinkedList* LL);
void del(struct LinkedList* LL);
#endif
