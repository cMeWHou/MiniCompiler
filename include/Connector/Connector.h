#ifndef WINSOCKET
#define WINSOCKET

#include <winsock.h>

#include <General/Common.h>

typedef struct SConnector {
    WSADATA         wsaData;

    SOCKET          server;
    SOCKET          client;

    SOCKADDR_IN     serverAddr;
    SOCKADDR_IN     clientAddr;
    int             clientAddrLength;

    void            (*WinsockStartup)   (WORD, LPWSADATA);
    SOCKET          (*Socket)           (int, int, int);
    void            (*Configure)        (SOCKADDR_IN*, string, int);
    void            (*Bind)             (SOCKET, SOCKADDR*, int);
    void            (*Listen)           (SOCKET, int);
    SOCKET          (*Accept)           (SOCKET, SOCKADDR*, int*);
    void            (*CloseSocket)      (SOCKET);

    void            (*MemoryRelease)    (struct SConnector*);
} TConnector;
TConnector*         Connector           (string, int);

#endif
