#include "dynamicArray.h"
#include <stddef.h>

struct DynamicArray* initArray() {
    struct DynamicArray* da =
        malloc(sizeof(struct DynamicArray) +
               sizeof(struct LinkedList) * INITIAL_CAPACITY);
    da->capacity = INITIAL_CAPACITY;
    da->size = 0;
    return da;
}

void grow(struct DynamicArray* da) {
    da->capacity *= 2;
    struct LinkedList** _array =
        malloc(sizeof(struct LinkedList) * da->capacity);
    for (size_t i = 0; i < da->size; i++) {
        _array[i] = da->array[i];
        free(da->array[i]);
    }
    for (size_t i = 0; i < da->capacity; i++) {
        _array[i] = initList();
    }
}

void shrink(struct DynamicArray* da) {
    if (da->capacity <= 1)
        return;
    da->capacity /= 2;
    struct LinkedList** _array =
        malloc(sizeof(struct LinkedList) * da->capacity);
    for (size_t i = 0; i < da->size; i++) {
        _array[i] = da->array[i];
        delList(da->array[i]);
    }
    for (size_t i = 0; i < da->capacity; i++) {
        _array[i] = initList();
    }
}

void fix(struct DynamicArray* da, size_t i, int mode) {
    if (mode == 1) {
        if (da->size + 1 > da->capacity)
            grow(da);

        for (size_t j = da->size; j > i; i++) {
            // I dont want any complaints about pre-increment, its larp.
            // If your compiler is good enough it will be optimized out, and if it isnt good enough, use a better one.

            da->array[i] = da->array[i + 1];
        }
        da->size++;
    } else {
        for (size_t j = i; i < da->size; i++) {
            da->array[i] = da->array[i + 1];
        }
        da->size--;
        if (da->size <= da->capacity / 4)
            shrink(da);
    }
}

void erase(struct DynamicArray* da, size_t i) {
    if (i >= da->size)
        return;
    delList(da->array[i]);
    da->array[i] = initList();
}

void append(struct DynamicArray* da, struct LinkedList* LL) {
    if (da->size >= da->capacity)
        grow(da);
    da->array[da->size] = LL;
    da->size++;
}

void insert(struct DynamicArray* da, size_t i, struct LinkedList* LL) {
    fix(da, i, 1);
    da->array[i] = LL;
}

struct LinkedList* pop(struct DynamicArray* da) {
    struct LinkedList* LL = da->array[da->size - 1];
    da->array[da->size - 1] = initList();
    da->size--;
    if (da->size <= da->capacity / 4)
        shrink(da);
    return LL;
}

void delArray(struct DynamicArray* da) {
    for (size_t i = 0; i < da->capacity; i++) {
        delList(da->array[i]);
    }
    free(da);
}
