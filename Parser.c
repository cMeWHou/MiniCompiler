#include <Lexer\Lexer.h>
#include <Parser\Parser.h>

#include <stdio.h>
#include <stdlib.h>

#include <General\Common.h>

static TNode *Term(TParser *);
static TNode *Summ(TParser *this);
static TNode *Test(TParser *);
static TNode *Expr(TParser *);
static TNode *ParenExpr(TParser *);
static TNode *Statement(TParser *);
static TNode *Parse(TParser *);

static void MemoryRelease(TParser *);

TParser *Parser(TLexer *lexer) {
    TParser *this = malloc(sizeof(TParser));

    this->Term = Term;
    this->Summ = Summ;
    this->Test = Test;
    this->Expr = Expr;
    this->ParenExpr = ParenExpr;
    this->Statement = Statement;
    this->Parse = Parse;

    this->MemoryRelease = MemoryRelease;

    // CTR
    this->lexer = lexer;
    // ECTR

    return this;
}

static TNode *Term(TParser *this) {
    TNode *node;
    if (this->lexer->Type == ID) {
        node = new Node(VAR, this->lexer->Value, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);
        return node;
    } else if (this->lexer->Type == NUM) {
        node = new Node(CONST, this->lexer->Value, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);
        return node;
    } else {
        return this->ParenExpr(this);
    }
}

static TNode *Summ(TParser *this) {
    TNode *node = this->Term(this);
    TType kind;
    while (this->lexer->Type == PLUS || this->lexer->Type == MINUS) {
        if (this->lexer->Type == PLUS) {
            kind = ADD;
        } else {
            kind = SUB;
        }
        this->lexer->NextToken(this->lexer);
        node = new Node(kind, __ZERO_VAL__, node, this->Term(this), __ZERO_PTR__);
    }

    return node;
}

static TNode *Test(TParser *this) {
    TNode *node = this->Summ(this);
    if (this->lexer->Type == LESS) {
        this->lexer->NextToken(this->lexer);
        node = new Node(LT, __ZERO_VAL__, node, this->Summ(this), __ZERO_PTR__);
    }

    return node;
}

static TNode *Expr(TParser *this) {
    if (this->lexer->Type != ID) {
        return this->Test(this);
    }

    TNode *node = this->Test(this);
    if (node->Kind == VAR && this->lexer->Type == EQUAL) {
        this->lexer->NextToken(this->lexer);
        node = new Node(SET, __ZERO_VAL__, node, this->Expr(this), __ZERO_PTR__);
    }

    return node;
}

static TNode *ParenExpr(TParser *this) {
    if (this->lexer->Type != LPAR) {
        printf("\'(\' expected");
    }
    this->lexer->NextToken(this->lexer);

    TNode *node = this->Expr(this);
    if (this->lexer->Type != RPAR) {
        printf("\')\' expected");
    }
    this->lexer->NextToken(this->lexer);

    return node;
}

static TNode *Statement(TParser *this) {
    TNode *node;
    if (this->lexer->Type == IF) {
        node = new Node(IF1, __ZERO_VAL__, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);

        node->Op1 = this->ParenExpr(this);
        node->Op2 = this->Statement(this);

        if (this->lexer->Type == ELSE) {
            node->Kind = IF2;
            this->lexer->NextToken(this->lexer);
            node->Op3 = this->Statement(this);
        }
    } else if (this->lexer->Type == WHILE) {
        node = new Node(LOOP, __ZERO_VAL__, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);

        node->Op1 = this->ParenExpr(this);
        node->Op2 = this->Statement(this);
    } else if (this->lexer->Type == DO) {
        node = new Node(THEN, __ZERO_VAL__, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);

        node->Op1 = this->Statement(this);

        if (this->lexer->Type != WHILE) {
            printf("\'while\' expected");
        }

        this->lexer->NextToken(this->lexer);
        node->Op2 = this->ParenExpr(this);

        if (this->lexer->Type != SEMICOLON) {
            printf("\';\' expected");
        }
    } else if (this->lexer->Type == SEMICOLON) {
        node = new Node(EMPTY, __ZERO_VAL__, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);
    } else if (this->lexer->Type == LBRA) {
        node = new Node(EMPTY, __ZERO_VAL__, __ZERO_PTR__, __ZERO_PTR__, __ZERO_PTR__);
        this->lexer->NextToken(this->lexer);

        while (this->lexer->Type != RBRA) {
            node = new Node(SEQ, __ZERO_VAL__, node, this->Statement(this), __ZERO_PTR__);
        }

        this->lexer->NextToken(this->lexer);
    } else {
        node = new Node(EXPR, __ZERO_VAL__, this->Expr(this), __ZERO_PTR__, __ZERO_PTR__);

        if (this->lexer->Type != SEMICOLON) {
            printf("\';\' expected");
        }

        this->lexer->NextToken(this->lexer);
    }

    return node;
}

static TNode *Parse(TParser *this) {
    this->lexer->NextToken(this->lexer);

    TNode *node = new Node(PROG, __ZERO_VAL__, this->Statement(this), __ZERO_PTR__, __ZERO_PTR__);

    if (this->lexer->Type != END) {
        printf("parser: invalid statement syntax\n");
    }

    return node;
}

static void MemoryRelease(TParser *this) {
    free(this);

    this = __ZERO_PTR__;
}