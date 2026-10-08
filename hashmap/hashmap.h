#ifndef HASH_MAP
#define HASH_MAP
#define INITIAL_HASH_SIZE 16
#include "../dynamicArray/dynamicArray.h"
#include <stdint.h>
#include <stdlib.h>
struct HashMap {
    struct DynamicArray* HashArray;
    size_t capacity;
};
struct HashMap* initHashMap();
void insertHm(struct HashMap* hm, char* l, Token t);
const Token findHm(struct HashMap* hm, const uint8_t* l);
int hash(const uint8_t* l);
void update(struct HashMap* hm, char* l, Token t);
//struct Node* remove(struct HashMap* hm, char* l);
void rebuild(struct HashMap* hm);
const size_t size(struct HashMap* hm);
int contains(struct HashMap* hm, char* l);
void delMap(struct HashMap* hm);
#endif
