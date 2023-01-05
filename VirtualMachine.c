#include <VM\Instruction.h>
#include <VM\VirtualMachine.h>

#include <stdio.h>
#include <stdlib.h>

#include "VM/Stack.h"

#include "General/Common.h"

void Run(TStack *);

TVirtualMachine *VirtualMachine() {
    TVirtualMachine *this = malloc(sizeof(TVirtualMachine));

    this->Run = Run;

    return this;
}

#define SIZE 26

void Run(TStack *program) {
    int var[SIZE];
    for (int i = 0; i < SIZE; i++) {
        var[i] = 0;
    }

    TStack *stack = new Stack();
    int pc = 0;

    while (1) {
        TInstruction op = program->Array[pc];
        int arg;
        if (pc < program->Size - 1) {
            arg = program->Array[pc + 1];
        }

        if (op == IFETCH) {
            stack->Push(stack, var[arg - 'a']);
            pc += 2;
        } else if (op == ISTORE) {
            var[arg - 'a'] = stack->Pop(stack);
            pc += 2;
        } else if (op == IPUSH) {
            stack->Push(stack, arg);
            pc += 2;
        } else if (op == IPOP) {
            stack->Push(stack, arg);
            stack->Pop(stack);
            pc += 1;
        } else if (op == IADD) {
            stack->Array[stack->Size - 2] += stack->Array[stack->Size - 1];
            stack->Pop(stack);
            pc += 1;
        } else if (op == ISUB) {
            stack->Array[stack->Size - 2] -= stack->Array[stack->Size - 1];
            stack->Pop(stack);
            pc += 1;
        } else if (op == ILT) {
            if (stack->Array[stack->Size - 2 < stack->Array[stack->Size - 1]]) {
                stack->Array[stack->Size - 2] = 1;
            } else {
                stack->Array[stack->Size - 2] = 0;
            }
            stack->Pop(stack);
            pc += 1;
        } else if (op == JZ) {
            if (stack->Pop(stack) == 0) {
                pc = arg;
            } else {
                pc += 2;
            }
        } else if (op == JNZ) {
            if (stack->Pop(stack) != 0) {
                pc = arg;
            } else {
                pc += 2;
            }
        } else if (op == JMP) {
            pc = arg;
        } else if (op == HALT) {
            break;
        }
    }

    printf("Execution finished.\n");
    for (int i = 0; i < SIZE; i++) {
        if (var[i] != 0) {
            printf("%c = %d\n", (char) (i + 'a'), var[i]);
        }
    }
}