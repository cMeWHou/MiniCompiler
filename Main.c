// EntryPoint

#include <Socket/Connector.h>
#include <Socket/Server.h>
#include <Socket/Exchange.h>

#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <Compiler/Compiler.h>
#include <VM/VirtualMachine.h>

#include <General/Common.h>

int main(int argc, char *argv[]) {
    // listening connection
    TConnector* connector   = new Connector("127.0.0.1", 5555);
    TServer* server         = new Server(serverSend, serverRecieve, &connector->client);

    string pathToSrcFile; // need to be modified

    // generating code
    TLexer*     lexer       = new Lexer(pathToSrcFile);

    TParser*    parser      = new Parser(lexer);
    TNode*      ast         = parser->Parse(parser);

    TCompiler*  compiler    = new Compiler();
    TStack*     program     = compiler->Compile(compiler, ast);

    // running program
    TVirtualMachine* vm     = new VirtualMachine();
    vm->Run(program);

    // memory release
    vm->MemoryRelease(vm);
    compiler->MemoryRelease(compiler);
    parser->MemoryRelease(parser);
    lexer->MemoryRelease(lexer);
    server->MemoryRelease(server);
    connector->MemoryRelease(connector);

    return 0;
}