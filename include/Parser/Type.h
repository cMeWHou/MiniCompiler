// List of available node types

#ifndef TYPE
#define TYPE

typedef enum EType {
    VAR,    IMMUT,
    ADD,    SUB,
    LT,
    SET,
    IF1,    IF2,
    LOOP,   THEN,
    EMPTY,
    SEQ,
    EXPR,
    PROG
} TType;

#endif