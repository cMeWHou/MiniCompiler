// VM struct

#ifndef VM
#define VM

#include <VM\Stack.h>

typedef struct SVirtualMachine {
    void            (*Run)          (TStack *);
} TVirtualMachine;
TVirtualMachine*    VirtualMachine  ();

#endif