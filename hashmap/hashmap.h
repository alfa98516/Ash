#ifndef HASH_MAP
#define HASH_MAP
#define INITIAL_HASH_SIZE 16
#include "../linkedlist/linkedlist.h"
#include <stdlib.h>
struct HashMap {
    struct LinkedList* hm[INITIAL_HASH_SIZE];
    size_t capacity;
};
struct HashMap* initHashMap();
Token find(char* t);
int hash(char* t);

#endif
