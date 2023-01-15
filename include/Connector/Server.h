#ifndef SERVER
#define SERVER

#include <winsock.h>

DWORD WINAPI ServerRecieve(LPVOID);
DWORD WINAPI ServerSend(LPVOID);

typedef struct SServer {
    HANDLE          recieveTask;
    HANDLE          sendTask;

    void            (*Start)        (struct SServer*);
} TServer;
TServer*            Server          (DWORD (*)(LPVOID),
                                     DWORD (*)(LPVOID),
                                     SOCKET*
                                     );

#endif
