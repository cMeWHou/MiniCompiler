// [key:lexeme] dictionary container

#ifndef LEXER_DICTIONARY
#define LEXER_DICTIONARY

#include <Lexer\Lexeme.h>

typedef struct SDictionary {
    char*       Key;
    TLexeme*    Value;
    int         Size;

    void        (*Append)   (struct SDictionary *, char, TLexeme);
    void        (*Remove)   (struct SDictionary *, char);
    int         (*Contains) (struct SDictionary *, char);
    int         (*GetValue) (struct SDictionary *, char);
} TDictionary;
TDictionary*    Dictionary  (int);

#endif