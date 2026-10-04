#ifndef HASH_MAP
#define HASH_MAP
#define INITIAL_HASH_SIZE 16
#include "../linkedlist/linkedlist.h"
#include <stdlib.h>
struct HashMap {
    struct LinkedList** HashArray;
    size_t capacity;
};
struct HashMap* initHashMap();
Token find(char* l);
int hash(char* l);
void update(char* l, Token t);
struct Node* remove(char* l);
void rebuild(struct HashMap h);
#endif
