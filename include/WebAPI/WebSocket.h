#ifndef WEBSOCKET
#define WEBSOCKET

#include <winsock.h>

void CloseSocket(SOCKET);

typedef struct SWebSocket {
    SOCKET      socket;
    SOCKADDR_IN address;
    int         addressLength;

    void        (*SetSocket)    (struct SWebSocket*, SOCKET);
    void        (*SetAddress)   (struct SWebSocket*, SOCKADDR_IN);

    void        (*MemoryRelease)(struct SWebSocket*);
} TWebSocket;
TWebSocket*     WebSocket       ();

#endif
