#include <Parser\Node.h>

#include <stdlib.h>

TNode *Node(TType kind, int value, TNode *op1, TNode *op2, TNode *op3) {
    TNode *this = malloc(sizeof(TNode));

    this->Kind = kind;
    this->Value = value;
    this->Op1 = op1;
    this->Op2 = op2;
    this->Op3 = op3;

    return this;
}