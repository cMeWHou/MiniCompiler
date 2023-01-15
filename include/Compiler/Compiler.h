// Compiler data from AST-from to Stack-container form

#ifndef COMPILER
#define COMPILER

#include <Parser/Node.h>
#include <VM/Stack.h>
#include <VM/Instruction.h>

typedef struct SCompiler {
    TStack* Program;
    int     Pcounter;

    void    (*Gen)          (struct SCompiler *, TInstruction);
    TStack* (*Compile)      (struct SCompiler *, TNode*);

    void    (*MemoryRelease)(struct SCompiler *);
} TCompiler;
TCompiler*  Compiler        ();

#endif