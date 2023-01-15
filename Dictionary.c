#include <Lexer/Dictionary.h>
#include <Lexer/Lexeme.h>

#include <stdlib.h>

#include <General/Common.h>

static void Append(TDictionary *, char, TLexeme);
static void Remove(TDictionary *, char);
static int Contains(TDictionary *, char);
static int GetValue(TDictionary *, char);

static void MemoryRelease(TDictionary *);

TDictionary *Dictionary(int maxSize) {
    TDictionary *this = malloc(sizeof(TDictionary));

    this->Append = Append;
    this->Remove = Remove;
    this->Contains = Contains;
    this->GetValue = GetValue;
    this->MemoryRelease = MemoryRelease;

    // CTR
    this->Key = malloc(sizeof(char) * maxSize);
    this->Value = malloc(sizeof(TLexeme) * maxSize);

    this->Size = 0;
    // ECTR

    return this;
}

static void Append(TDictionary *this, char key, TLexeme value) {
    this->Key[this->Size] = key;
    this->Value[this->Size] = value;

    this->Size++;
}

static void Remove(TDictionary *this, char key) {
    for (int i = 0; i < this->Size; i++) {
        if (this->Key[i] == key) {
            for (int j = i; j < this->Size - 1; j++) {
                this->Key[j] = this->Key[j + 1];
                this->Value[j] = this->Value[j + 1];
            }
        }
    }

    this->Size--;
}

static int Contains(TDictionary *this, char key) {
    for (int i = 0; i < this->Size; i++) {
        if (this->Key[i] == key) {
            return 1;
        }
    }

    return 0;
}

static int GetValue(TDictionary *this, char key) {
    for (int i = 0; i < this->Size; i++) {
        if (this->Key[i] == key) {
            return this->Value[i];
        }
    }

    return __BAD_VAL__;
}

static void MemoryRelease(TDictionary *this) {
    free(this->Key);
    free(this->Value);
    free(this);

    this = __ZERO_PTR__;
}