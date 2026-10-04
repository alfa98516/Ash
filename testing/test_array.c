#include "../dynamicArray/dynamicArray.h"
#include <stdio.h>

int main() {
    struct DynamicArray* da = initArray();
    struct LinkedList* LL1 = initList();
    struct LinkedList* LL2 = initList();

    struct _TOKEN t1 = (struct _TOKEN){BANG, "!\0"};
    struct _TOKEN t2 = (struct _TOKEN){RBRACE, "}\0"};
    struct _TOKEN t3 = (struct _TOKEN){IN, "in\0"};
    struct _TOKEN t4 = (struct _TOKEN){FOR, "for\0"};
    prepend(LL1, t1);
    prepend(LL1, t2);
    prepend(LL2, t3);
    prepend(LL2, t4);
    append(da, LL1);
    append(da, LL2);

    for (int i = 0; i < da->size; i++) {
        struct Node* curr = da->array[i]->Head;
        while (curr != NULL) {
            printf("%s\n", curr->t.lexeme);
            curr = curr->next;
        }
    }
    delArray(da);
    return EXIT_SUCCESS;
}
