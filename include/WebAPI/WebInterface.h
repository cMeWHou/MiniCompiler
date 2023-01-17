#ifndef WINSOCKET
#define WINSOCKET

#include <WebAPI/WebSocket.h>

#include <winsock.h>

#include <General/Common.h>

typedef struct SWebInterface {
    WSADATA         wsaData;

    TWebSocket*     serverSocket;
    TWebSocket*     clientSocket;

    void              (*MemoryRelease)    (struct SWebInterface*);
} TWebInterface;
TWebInterface*        WebInterface        (string, int);

#endif
