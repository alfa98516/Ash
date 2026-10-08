#include "hashmap.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

struct HashMap* initHashMap() {
    struct HashMap* hm = malloc(sizeof(struct HashMap));
    hm->HashArray = initArray();
    hm->capacity = INITIAL_HASH_SIZE;
    return hm;
}

int hash(const uint8_t* l) {
    size_t hash = 0;
    size_t len = strlen((const char*)l);
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
    return len;
}

void insertHm(struct HashMap* hm, char* l, Token t) {
    if (size(hm) > hm->capacity * 0.75) {
        rebuild(hm);
    }
    size_t i = hash((const uint8_t*)l) % hm->capacity;
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
            size_t hashed = hash((const uint8_t*)node->t.lexeme) % capacity;
            struct _TOKEN newT;
            memcpy(newT.lexeme, node->t.lexeme, strlen(node->t.lexeme) + 1);
            newT.tokenId = node->t.tokenId;
            prepend(HashArray->array[hashed], newT);
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
