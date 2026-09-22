#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER
#include "token.h"
void init();
bool peek_rune_is(char rune);
void next_rune();
char* word();
char* number();
bool white_space();
Token next_token();
#endif
