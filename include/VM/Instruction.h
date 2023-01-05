// List of available instructions in VM

#ifndef INSTRUCTION
#define INSTRUCTION

typedef enum EInstruction {
    IFETCH, ISTORE,
    IPUSH,  IPOP,
    IADD,   ISUB,
    ILT,
    JZ,     JNZ,    JMP,
    HALT,
} TInstruction;

#endif