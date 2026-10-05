#include "hashmap.h"

struct HashMap* initHashMap() {
    struct HashMap* hm = malloc(sizeof(struct HashMap));
    hm->HashArray = initArray();
    hm->capacity = INITIAL_HASH_SIZE;
    return hm;
}

Token find(struct HashMap* hm, char* l) {}

int hash(struct HashMap* hm, char* l) {}

void update(struct HashMap* hm, char* l, Token t) {}

struct Node* remove(struct HashMap* hm, char* l) {}

void rebuild(struct HashMap* hm) {}
