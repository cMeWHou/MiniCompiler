#include <Parser\Node.h>

#include <stdlib.h>

#include <General\Common.h>

static void MemoryRelease(TNode *);

TNode *Node(TType kind, int value, TNode *op1, TNode *op2, TNode *op3) {
    TNode *this = malloc(sizeof(TNode));

    this->MemoryRelease = MemoryRelease;

    this->Kind = kind;
    this->Value = value;
    this->Op1 = op1;
    this->Op2 = op2;
    this->Op3 = op3;

    return this;
}

static void MemoryRelease(TNode *this) {
    free(this);

    this = __ZERO_PTR__;
}