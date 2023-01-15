// VM struct

#ifndef VM
#define VM

#include <VM/Stack.h>

typedef struct SVirtualMachine {
    void            (*Run)          (TStack *);

    void            (*MemoryRelease)(struct SVirtualMachine *);
} TVirtualMachine;
TVirtualMachine*    VirtualMachine  ();

#endif