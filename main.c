#include <stdio.h>
#include <string.h>

void incr(char** a) {
    int n = strlen(*a);
    a++;
    *a[n - 2] = '\0';
}

int main() {
    char* a = "testing123";
    printf("%s", a);
    incr(&a);
    printf("%s", a);
}
