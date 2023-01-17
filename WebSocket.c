#include <WebAPI/WebSocket.h>

#include <stdio.h>
#include <stdlib.h>

#include <General/Common.h>

void CloseSocket(SOCKET);
static void SetSocket(TWebSocket*, SOCKET);
static void SetAddress(TWebSocket*, SOCKADDR_IN);
static void MemoryRelease(TWebSocket*);

TWebSocket* WebSocket() {
    TWebSocket* this = malloc(sizeof(TWebSocket));

    this->MemoryRelease = MemoryRelease;

    // CTR
    this->addressLength = sizeof(this->address);
    // ECTR

    return this;
}

void CloseSocket(SOCKET socket) {
    if (closesocket(socket) == SOCKET_ERROR) {
        printf("closesocket() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static void SetSocket(TWebSocket* websocket, SOCKET socket) {
    websocket->socket = socket;
}

static void SetAddress(TWebSocket* websocket, SOCKADDR_IN address) {
    websocket->address = address;
}

static void MemoryRelease(TWebSocket* this){
    CloseSocket(this->socket);

    free(this);

    this = __ZERO_PTR__;
}