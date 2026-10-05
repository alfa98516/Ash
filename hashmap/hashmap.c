#include "hashmap.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
struct HashMap* initHashMap() {
    struct HashMap* hm = malloc(sizeof(struct HashMap));
    hm->HashArray = initArray();
    hm->capacity = INITIAL_HASH_SIZE;
    return hm;
}

int hash(const uint8_t* l) {
    size_t hash = 0;
    size_t len = strlen(l);
    for (size_t i = 0; i < len; i++) {
        hash = hash * 31 + l[i];
    }
    return hash;
}

const size_t size(struct HashMap* hm) {
    size_t len = 0;
    for (size_t i = 0; i < hm->HashArray->capacity; i++) {
        if (hm->HashArray->array[i]->Head != NULL) {
            len += length(hm->HashArray->array[i]);
        }
    }
}

void insertHm(struct HashMap* hm, char* l, Token t) {
    if (size(hm) > hm->capacity * 0.75)
        rebuild(hm);
    size_t i = hash(l) % hm->capacity;
    prepend(hm->HashArray->array[i], t);
}

const Token findHm(struct HashMap* hm, const uint8_t* l) {
    size_t i = hash(l) % hm->capacity;
    const Token t = find(hm->HashArray->array[i], l);
    return t;
}

void __update(struct HashMap* hm, char* l, Token t) {
    return; // not sure i will need this one
}

struct Node* __remove(struct HashMap* hm, char* l) {
    return hm->HashArray->array[0]
        ->Head; // once again, im kind of not using this
}

void rebuild(struct HashMap* hm) {
    size_t capacity = hm->capacity * 2;
    struct DynamicArray* HashArray = initArrayCapacity(capacity);

    for (size_t i = 0; i < hm->capacity; i++) {
        struct Node* node = hm->HashArray->array[i]->Head->next;
        while (node != hm->HashArray->array[i]->Tail) {
            size_t hashed = hash(node->t.lexeme) % capacity;
            prepend(HashArray->array[i], node->t);
            node = node->next;
        }
    }
    hm->capacity = capacity;
    delArray(hm->HashArray);
    hm->HashArray = HashArray;
}

void delMap(struct HashMap* hm) {
    delArray(hm->HashArray);
    free(hm);
}
