// EntryPoint
#include <WebAPI/Exchange.h>

#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <Compiler/Compiler.h>
#include <VM/VirtualMachine.h>

#include <General/Common.h>

int main(int argc, char *argv[]) {
    // listening connection
    string serverIP = "127.0.0.1";
    int port = 8585;

    TWebInterface* webInterface = new WebInterface(serverIP, port);
    TExchange* exchange         = new Exchange(webInterface);
    exchange->Start(exchange);

    string pathToSrcFile; // TODO: need to be modified

    // generating code
    TLexer*     lexer           = new Lexer(pathToSrcFile);

    TParser*    parser          = new Parser(lexer);
    TNode*      ast             = parser->Parse(parser);

    TCompiler*  compiler        = new Compiler();
    TStack*     program         = compiler->Compile(compiler, ast);

    // running program
    TVirtualMachine* vm         = new VirtualMachine();
    vm->Run(program);

    // memory release
    vm->MemoryRelease(vm);
    compiler->MemoryRelease(compiler);
    parser->MemoryRelease(parser);
    lexer->MemoryRelease(lexer);
    exchange->MemoryRelease(exchange);
    webInterface->MemoryRelease(webInterface);

    return 0;
}