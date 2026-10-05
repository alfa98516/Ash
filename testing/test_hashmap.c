#include "../hashmap/hashmap.h"
#include <stdio.h>
int main() {
    struct HashMap* hm = initHashMap();
    struct _TOKEN ForKw = (struct _TOKEN){FOR, "for\0"};
    struct _TOKEN InKw = (struct _TOKEN){IN, "in\0"};
    struct _TOKEN IfKw = (struct _TOKEN){IF, "if\0"};
    struct _TOKEN CaseKw = (struct _TOKEN){CASE, "case\0"};
    struct _TOKEN ThenKw = (struct _TOKEN){THEN, "then\0"};
    insertHm(hm, "for\0", ForKw);
    insertHm(hm, "in\0", InKw);
    insertHm(hm, "if\0", IfKw);
    insertHm(hm, "case\0", CaseKw);
    insertHm(hm, "then\0", ThenKw);

    printf("%s\n", findHm(hm, "for\0").lexeme);
    printf("%s\n", findHm(hm, "in\0").lexeme);
    printf("%s\n", findHm(hm, "if\0").lexeme);
    printf("%s\n", findHm(hm, "case\0").lexeme);
    printf("%s\n", findHm(hm, "then\0").lexeme);
    delMap(hm);
}
