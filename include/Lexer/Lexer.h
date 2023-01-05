// Lexer struct

#ifndef LEXER
#define LEXER

#include <Lexer\Lexeme.h>
#include <Lexer\Dictionary.h>

#include <stdio.h>

typedef struct SLexer {
    FILE*           sourceCode;

    char            Char;

    int             Value;
    TLexeme         Type;

    TDictionary*    Symbols;
    TDictionary*    Words;

    char            (*NextChar) (struct SLexer *);
    void            (*NextToken)(struct SLexer *);
} TLexer;
TLexer*             Lexer       (char *);

#endif