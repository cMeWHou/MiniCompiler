// Stack container

#ifndef STACK
#define STACK

typedef struct SStack {
    int*    Array;
    int     Size;

    void    (*Push)         (struct SStack *, int);
    int     (*Pop)          (struct SStack *);

    void    (*MemoryRelease)(struct SStack *);
} TStack;
TStack*     Stack           ();

#endif