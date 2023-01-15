#ifndef SERVER
#define SERVER

#include <winsock.h>

DWORD WINAPI ServerRecieve(LPVOID);
DWORD WINAPI ServerSend(LPVOID);

typedef struct SServer {
    HANDLE          recieveTask;
    HANDLE          sendTask;

    SOCKET*         client;

    DWORD           (*Send)         (LPVOID);
    DWORD           (*Receive)      (LPVOID);
    void            (*Start)        (struct SServer*);

    void            (*MemoryRelease)(struct SServer*);
} TServer;
TServer*            Server          (DWORD (*)(LPVOID),
                                     DWORD (*)(LPVOID),
                                     SOCKET*
                                     );

#endif
