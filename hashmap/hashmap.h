#ifndef HASH_MAP
#define HASH_MAP
#define INITIAL_HASH_SIZE 16
#include "../dynamicArray/dynamicArray.h"
#include "../linkedlist/linkedlist.h"
#include <stdlib.h>
struct HashMap {
    struct DynamicArray* HashArray;
    size_t capacity;
};
struct HashMap* initHashMap();
Token find(struct HashMap* hm, char* l);
int hash(struct HashMap* hm, char* l);
void update(struct HashMap* hm, char* l, Token t);
struct Node* remove(struct HashMap* hm, char* l);
void rebuild(struct HashMap* hm);
#endif
