// [key:lexeme] dictionary container

#ifndef LEXER_DICTIONARY
#define LEXER_DICTIONARY

#include <Lexer\Lexeme.h>

#include <General\Common.h>

typedef struct SDictionary {
    string      Key;
    TLexeme*    Value;
    int         Size;

    void        (*Append)       (struct SDictionary *, char, TLexeme);
    void        (*Remove)       (struct SDictionary *, char);
    int         (*Contains)     (struct SDictionary *, char);
    int         (*GetValue)     (struct SDictionary *, char);

    void        (*MemoryRelease)(struct SDictionary *);
} TDictionary;
TDictionary*    Dictionary      (int);

#endif