#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include "../linkedlist/linkedlist.h"
#include <stdlib.h>
struct DynamicArray {
    struct LinkedList** array;
    size_t size;
    size_t capacity;
};
struct DynamicArray* initArray();
void grow(struct DynamicArray* da);
void shrink(struct DynamicArray* da);
void fix(struct DynamicArray* da, size_t i, int mode);
void erase(struct DynamicArray* da, size_t i);
void append(struct DynamicArray* da, struct LinkedList* LL);
void insert(struct DynamicArray* da, struct LinkedList* LL);
struct LinkedList* pop(struct DynamicArray* da);
struct LinkedList* get(struct DynamicArray* da, size_t i);
void delArray(struct DynamicArray* da);
#endif
