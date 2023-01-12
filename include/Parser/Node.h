// Node struct

#ifndef NODE
#define NODE

#include <Parser\Type.h>

typedef struct SNode {
    TType           Kind;
    int             Value;

    struct SNode*   Op1;
    struct SNode*   Op2;
    struct SNode*   Op3;

    void            (*MemoryRelease)(struct SNode *);
} TNode;
TNode*              Node            (TType, int, TNode *, TNode *, TNode *);

#endif