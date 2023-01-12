#include <Compiler\Compiler.h>
#include <Parser\Node.h>
#include <VM\Instruction.h>
#include <VM\Stack.h>

#include <stdlib.h>

#include <General\Common.h>

static void Gen(TCompiler *, TInstruction);
static TStack *Compile(TCompiler *, TNode *);

static void MemoryRelease(TCompiler *);

TCompiler *Compiler() {
    TCompiler *this = malloc(sizeof(TCompiler));

    this->Gen = Gen;
    this->Compile = Compile;
    this->MemoryRelease = MemoryRelease;

    //CTR
    this->Program = new Stack();
    this->Pcounter = 0;
    //ECTR

    return this;
}

static void Gen(TCompiler *this, TInstruction command) {
    this->Program->Push(this->Program, command);
    this->Pcounter += 1;
}

static TStack *Compile(TCompiler *this, TNode *node) {
    int addr;
    int sAddr;

    if (node->Kind == VAR) {
        this->Gen(this, IFETCH);
        this->Gen(this, node->Value);
    } else if (node->Kind == CONST) {
        this->Gen(this, IPUSH);
        this->Gen(this, node->Value);
    } else if (node->Kind == ADD) {
        this->Compile(this, node->Op1);
        this->Compile(this, node->Op2);
        this->Gen(this, IADD);
    } else if (node->Kind == SUB) {
        this->Compile(this, node->Op1);
        this->Compile(this, node->Op2);
        this->Gen(this, ISUB);
    } else if (node->Kind == LT) {
        this->Compile(this, node->Op1);
        this->Compile(this, node->Op2);
        this->Gen(this, ILT);
    } else if (node->Kind == SET) {
        this->Compile(this, node->Op2);
        this->Gen(this, ISTORE);
        this->Gen(this, node->Op1->Value);
    } else if (node->Kind == IF1) {
        this->Compile(this, node->Op1);
        this->Gen(this, JZ);
        addr = this->Pcounter;
        this->Gen(this, 0);
        this->Program->Array[addr] = this->Pcounter;
    } else if (node->Kind == IF1) {
        this->Compile(this, node->Op1);
        this->Gen(this, JZ);
        addr = this->Pcounter;
        this->Gen(this, 0);

        this->Compile(this, node->Op2);
        this->Gen(this, JMP);
        sAddr = this->Pcounter;
        this->Gen(this, 0);

        this->Program->Array[addr] = this->Pcounter;
        this->Compile(this, node->Op3);
        this->Program->Array[sAddr] = this->Pcounter;
    } else if (node->Kind == LOOP) {
        addr = this->Pcounter;
        this->Compile(this, node->Op1);
        this->Gen(this, JZ);
        sAddr = this->Pcounter;
        this->Gen(this, 0);

        this->Compile(this, node->Op2);
        this->Gen(this, JMP);
        this->Gen(this, addr);
        this->Program->Array[sAddr] = this->Pcounter;
    } else if (node->Kind == THEN) {
        addr = this->Pcounter;
        this->Compile(this, node->Op1);
        this->Compile(this, node->Op2);
        this->Gen(this, JZ);
        this->Gen(this, addr);
    } else if (node->Kind == SEQ) {
        this->Compile(this, node->Op1);
        this->Compile(this, node->Op2);
    } else if (node->Kind == EXPR) {
        this->Compile(this, node->Op1);
        this->Gen(this, IPOP);
    } else if (node->Kind == PROG) {
        this->Compile(this, node->Op1);
        this->Gen(this, HALT);
    }

    return this->Program;
}

static void MemoryRelease(TCompiler *this){
    free(this);

    this = __ZERO_PTR__;
}