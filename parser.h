
#define MAX_ARG_NAME 255
typedef enum { ERROR = -1, CMD, CD, AMPERSAND, PIPE, FLAG, UNINIT } TokenId;

typedef struct {
    TokenId tokenId;
    char lexeme[MAX_ARG_NAME];
} Token;

void tokenize(char* cmd);
