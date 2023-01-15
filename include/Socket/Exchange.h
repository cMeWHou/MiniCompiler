#ifndef EXCHANGE
#define EXCHANGE

#include <winsock.h>

#define BUFFER_SIZE 512

DWORD WINAPI serverRecieve(LPVOID);
DWORD WINAPI serverSend(LPVOID);

#endif
