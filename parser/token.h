#ifndef TOKEN
#define TOKEN
/* Copyright (c) 2026 Alfa Reynisdóttir. All Rights Reserved.
 *
 *
 *
 */

// I want my comments looking nice sorry clangd.
// clang-format off

/*
 * Sources used:
 *  IEEE Std 1003.1, 2004 POSIX Shell Standard (https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
 *  The GNU Bash Manual (https://www.gnu.org/software/bash/manual/bash.html#Shell-Commands)
 *  Official Yacc Grammar for Bash (https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/parse.y)
 *
 * Currently there is a very sparse definition for the grammer of the Bourne Again Shell, which sort of makes sense, since the only thing we need to comply 
 * with is the POSIX definiton of a shell.
 * The problem with the POSIX definition is that it is extremely limited, there are barely any proper conditions.
 * The only real "complete" definition for the bash language, is in the Bash source code.
 */
typedef enum _TOKEN_ID {
    ERROR = 0,          // This will be the default token, might end up obsolete, but we
                        // will see.
    EOI,
    WORD,               /* This will encompess variable declerations and variable expansions, 
                         * in this case, functions are variables.
                         */
    ASSIGNMENT_WORD,    /* ASSIGNMENT_WORD is difined as anything of the form WORD=[VALUE] 
                         * If it is of the form WORD, it is just a word.
                         */
 
    NUMBER,             // [1-9] [0-9]*
    
    IO_NUMBER,          /* The POSIX Shell Standard defines a meaningful difference between normal
                         * integers and io numbers (file descriptors), from the POSIX Shell standard:
                         * "If the string consists solely of digits and the delimiter character is one of '<' or
                         * '>', the token identifier IO_NUMBER shall be returned." 
                         * If we get regex of the form: "[0-9]?(?:>>|<<|>|<)&?[0-9]?" the numbers in it are io_numbers (file descriptors)
                         *
                         */
   
    // Operators.
    AND,                // '&'
    AND_IF,             // '&&'
    OR_IF,              // '||'
    OR,                 // '|',
    SEMI,               // ';'
    DSEMI,              // ';;'
    DLESS,              // '<<'
    TLESS,              // '<<<' NOT THIS BULLSHIT AGAIN
    DGREAT,             // '>>'
    LESSAND,             // '<&'
    GREATAND,           // '>&'
    LESSGREAT,          // '<>'
    DLESSDASH,          // '<<-' This ones gonna be a bitch
    CLOBBER,            // '>|'  Yes that is actually what the token is called
    DASH,               // '-'
    DECR,               // 'DECR'
    PLUS,               // '+'
    INCR,               // '++'
    MUL,                // '*'
    DIV,                // '/' Bash does not have floating point but it does have division, 
                        //     it works like '//' in python
    
    

    /* Keywords.
     * In the POSIX Shell Standard, 
     * they have the keyword token variables in pascal-cased for some reason,
     * even though every other token is uppercase, I do not know why, 
     * it's not even the convention for most parsers I've read.
     */ 
    IF,                 // 'if'
    THEN,               // 'then'
    ELSE,               // 'else'
    ELIF,               // 'elif'
    FI,                 // 'fi'
    DO,                 // 'do'
    DONE,               // 'done'
    CASE,               // 'case'
    ESAC,               // 'while'
    UNTIL,              // 'until'
    FOR,                // 'for'

    /* From the POSIX Shell Standard: 
     * "These are reserved words, not operator tokens, and are
     *  recognized when reserved words are recognized." 
     */
    LBRACKET,           // '['
    RBRACKET,           // ']'
    LDBRACKET,          // '[['
    RDBRACKET,          // ']]'
    LBRACE,             // '{'
    RBRACE,             // '}'
    BANG,               // '!' Only grammer I've seen that calls it bang
    IN,                 // 'in'
    

} TokenId;
// clang-format on
#define MAX_ARG_NAME 255
typedef struct _TOKEN {
    TokenId tokenId;
    char lexeme[MAX_ARG_NAME];
} Token;
#endif
