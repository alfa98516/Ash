#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#define INITIAL_CAPACITY 16
#include "../linkedlist/linkedlist.h"
#include <stdlib.h>
struct DynamicArray {
    struct LinkedList** array;
    size_t size;
    size_t capacity;
};
struct DynamicArray* initArray();
struct DynamicArray* initArrayCapacity(size_t capacity);
void grow(struct DynamicArray* da);
void shrink(struct DynamicArray* da);
void fix(struct DynamicArray* da, size_t i, int mode);
void erase(struct DynamicArray* da, size_t i);
void append(struct DynamicArray* da, struct LinkedList* LL);
void insert(struct DynamicArray* da, size_t i, struct LinkedList* LL);
struct LinkedList* pop(struct DynamicArray* da);
void delArray(struct DynamicArray* da);
#endif
