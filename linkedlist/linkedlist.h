#ifndef LINKED_LIST
#define LINKED_LIST
#include "../parser/token.h"
struct Node {
    struct Node* next;
    Token t;
};

struct LinkedList {
    struct Node* Head;
    struct Node* Tail;
};

struct LinkedList* initList();
int isEmpty(struct LinkedList* LL);
void prepend(struct LinkedList* LL, Token data);
Token dequeue(struct LinkedList* LL);

// Making the user clean up the data structure would be unsafe,
// I provide a  deleate function for this.
void delList(struct LinkedList* LL);
#endif
