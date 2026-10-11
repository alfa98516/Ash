#include <signal.h>
#include <stdio.h>
#ifndef MACROS
#define MACROS
#define ASSERT(x)                                                              \
    do {                                                                       \
        if (!(x))                                                              \
            raise(SIGTRAP);                                                    \
    } while (0)
#endif
