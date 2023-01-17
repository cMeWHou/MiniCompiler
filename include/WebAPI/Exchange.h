#ifndef SERVER
#define SERVER

#include <WebAPI/WebInterface.h>

#include <winsock.h>

typedef struct SExchange {
    SOCKET*         client;

    void            (*Start)        (struct SExchange*);

    void            (*MemoryRelease)(struct SExchange*);
} TExchange;
TExchange*          Exchange        (TWebInterface*);

#endif
