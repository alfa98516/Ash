#include "hashmap.h"

struct HashMap* initHashMap() {
    struct LinkedList** ha = malloc(sizeof(struct LinkedList) * INITIAL_HASH_SIZE);
    struct HashMap* hm =
        malloc(sizeof(struct HashMap) + sizeof(struct LinkedList) * INITIAL_HASH_SIZE);
    hm->capacity = INITIAL_HASH_SIZE;
    return hm;
}

update
