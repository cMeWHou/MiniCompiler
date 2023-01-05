// Parser struct

#ifndef PARSER
#define PARSER

#include <Parser\Node.h>

#include <Lexer\Lexer.h>

typedef struct SParser {
  TLexer*   lexer;

  TNode*    (*Term)        (struct SParser *);
  TNode*    (*Summ)        (struct SParser *);
  TNode*    (*Test)        (struct SParser *);
  TNode*    (*Expr)        (struct SParser *);
  TNode*    (*ParenExpr)   (struct SParser *);
  TNode*    (*Statement)   (struct SParser *);
  TNode*    (*Parse)       (struct SParser *);
} TParser;
TParser*    Parser         (TLexer *);

#endif