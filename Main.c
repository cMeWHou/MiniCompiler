

#include <Compiler\Compiler.h>
#include <Lexer\Lexer.h>
#include <Parser\Parser.h>
#include "VM/Stack.h"
#include <VM\VirtualMachine.h>

#include "General/Common.h"

int main(int argc, char *argv[]) {
    TLexer *lexer = new Lexer(!argv[1] ? ".\\source.txt" : argv[1]);
    TParser *parser = new Parser(lexer);

    TNode *ast = parser->Parse(parser);

    TCompiler *compiler = new Compiler();
    TStack *program = compiler->Compile(compiler, ast);

    TVirtualMachine *vm = VirtualMachine();
    vm->Run(program);

    return 0;
}