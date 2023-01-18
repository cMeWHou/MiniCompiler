#ifndef SERVER
#define SERVER

#include <WebAPI/WebInterface.h>

#include <winsock.h>

#include <General/Common.h>

typedef struct SExchange {
    SOCKET*         client;

    string          (*Read)         (struct SExchange*);
    void            (*Send)         (struct SExchange*, string);

    void            (*MemoryRelease)(struct SExchange*);
} TExchange;
TExchange*          Exchange        (TWebInterface*);

#endif
