#include <VM\Stack.h>

#include <stdlib.h>

#include <General\Common.h>

static void Push(TStack *, int);
static int Pop(TStack *);

static void MemoryRelease(TStack *);

TStack *Stack() {
    TStack *this = malloc(sizeof(TStack));

    this->Push = Push;
    this->Pop = Pop;

    //CTR
    this->Array = __ZERO_PTR__;
    this->Size = __ZERO_VAL__;
    //ECTR

    return this;
}

static void Push(TStack *this, int elem) {
    this->Size++;

    if (this->Array)
        this->Array = realloc(this->Array, this->Size * sizeof(int));
    else
        this->Array = malloc(sizeof(int));

    this->Array[this->Size - 1] = elem;
}

static int Pop(TStack *this) {
    int ret = __BAD_VAL__;

    if (this->Size-- > __ZERO_VAL__) {
        ret = this->Array[this->Size];
        this->Array = realloc(this->Array, this->Size);
    }

    return ret;
}

static void MemoryRelease(TStack *this){
    free(this->Array);
    free(this);

    this = __ZERO_PTR__;
}