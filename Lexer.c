#include <Lexer/Lexer.h>
#include <Lexer/Dictionary.h>

#include <stdio.h>
#include <stdlib.h>

#include <General/Common.h>

#define SYMBOLS_COUNT 9
#define WORD_COUNT 4

static char NextChar(TLexer *);
static void NextToken(TLexer *);

static int IsExist(char);
static int IsDigit(char);
static int IsAlpha(char);

static void MemoryRelease(TLexer *);

TLexer *Lexer(string path) {
    TLexer *this = malloc(sizeof(TLexer));

    this->NextChar = NextChar;
    this->NextToken = NextToken;
    this->MemoryRelease = MemoryRelease;

    // CTR
    this->sourceCode = fopen(path, "r");

    this->Symbols = new Dictionary(SYMBOLS_COUNT);
    this->Symbols->Append(this->Symbols, '{', LBRA);
    this->Symbols->Append(this->Symbols, '}', RBRA);
    this->Symbols->Append(this->Symbols, '(', LPAR);
    this->Symbols->Append(this->Symbols, ')', RPAR);
    this->Symbols->Append(this->Symbols, '=', EQUAL);
    this->Symbols->Append(this->Symbols, ';', SEMICOLON);
    this->Symbols->Append(this->Symbols, '+', PLUS);
    this->Symbols->Append(this->Symbols, '-', MINUS);
    this->Symbols->Append(this->Symbols, '<', LESS);

    this->Words = new Dictionary(WORD_COUNT);
    this->Words->Append(this->Words, '?', IF);
    this->Words->Append(this->Words, ':', ELSE);
    this->Words->Append(this->Words, '$', WHILE);
    this->Words->Append(this->Words, '>', DO);

    this->Char = this->NextChar(this);
    // ECTR

    return this;
}

static char NextChar(TLexer *this) {
    return (char) fgetc(this->sourceCode);
}

static void NextToken(TLexer *this) {
    this->Type = __BAD_VAL__;
    this->Value = __ZERO_VAL__;

    while (this->Type == __BAD_VAL__) {
        if (!IsExist(this->Char)) {
            this->Type = END;
        } else if (this->Char == ' ') {
            this->Char = this->NextChar(this);
        } else if (this->Symbols->Contains(this->Symbols, this->Char)) {
            this->Type = this->Symbols->GetValue(this->Symbols, this->Char);
            if (this->Type == __BAD_VAL__)
                printf("lexer: cannot get any symbol by key \'%d\'\n", this->Char);

            this->Char = this->NextChar(this);
        } else if (this->Words->Contains(this->Words, this->Char)) {
            this->Type = this->Words->GetValue(this->Words, this->Char);
            if (this->Type == __BAD_VAL__)
                printf("lexer: cannot get any word by key \'%d\'\n", this->Char);

            this->Char = this->NextChar(this);
        } else if (IsDigit(this->Char)) {
            this->Type = NUM;
            int number = 0;

            while (IsDigit(this->Char)) {
                number = number * 10 + (this->Char - '0');
                this->Char = this->NextChar(this);
            }
            this->Value = number;
        } else if (IsAlpha(this->Char)) {
            this->Type = ID;
            this->Value = (int) this->Char;
            this->Char = this->NextChar(this);
        } else {
            printf("lexer: unknown symbol\n");
        }
    }
}

static int IsExist(char ch) {
    if (ch != '\n')
        return 1;
    return 0;
}

static int IsDigit(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

static int IsAlpha(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return 1;
    return 0;
}

static void MemoryRelease(TLexer *this) {
    fclose(this->sourceCode);

    free(this->Symbols);
    free(this->Words);
    free(this);

    this = __ZERO_PTR__;
}