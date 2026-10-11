#include <signal.h>
#include <stdio.h>
#define ASSERT(x)                                                                                  \
    do {                                                                                           \
        if (!(x)) raise(SIGTRAP);                                                                  \
    } while (0)
#define ERROR(x)                                                                                   \
    do {                                                                                           \
        fprintf(stderr, "%s: %s:%d\n", x, __FILE__, __LINE__);                                     \
        ASSERT(0);                                                                                 \
    } while (0)
