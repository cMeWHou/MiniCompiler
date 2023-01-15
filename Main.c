// EntryPoint

#include <Connector/Connector.h>
#include <Connector/Server.h>
#include <Connector/Exchange.h>

#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <Compiler/Compiler.h>
#include <VM/VirtualMachine.h>

#include <General/Common.h>

int main(int argc, char *argv[]) {
    TConnector* connector   = new Connector("127.0.0.1", 5555);
    TServer* server         = new Server(serverSend, serverRecieve, &connector->client); // need add MemoryRelease()

    string pathToSrcFile    = argv[argc - 1];

    TLexer*     lexer       = new Lexer(pathToSrcFile);

    TParser*    parser      = new Parser(lexer);
    TNode*      ast         = parser->Parse(parser);

    TCompiler*  compiler    = new Compiler();
    TStack*     program     = compiler->Compile(compiler, ast);

    TVirtualMachine* vm     = new VirtualMachine();
    vm->Run(program);

    // memory release
    vm->MemoryRelease(vm);
    compiler->MemoryRelease(compiler);
    parser->MemoryRelease(parser);
    lexer->MemoryRelease(lexer);
    connector->MemoryRelease(connector);

    return 0;
}