// List of available lexemes

#ifndef LEXEME
#define LEXEME

typedef enum ELexeme {
    NUM,    ID,     // nums and vars
    IF,     ELSE,   // flow control symbols '?' and ':' [v0.1 doesn't work]
    WHILE,  DO,     // loop control symbols '$' and '>' [v0.1 doesn't work]
    LBRA,   RBRA,   // statement symbols '{' and '}'
    LPAR,   RPAR,   // grouping symbols '(' and ')' [v0.1 doesn't work]
    PLUS,   MINUS,  // arithmetic operations '+' and '-'
    LESS,           // logic comparsion symbol '<'
    EQUAL,          // mathematic equal '='
    SEMICOLON,      // end of instruction symbol ';'
    END             // end of program symbol '\n'
} TLexeme;

#endif