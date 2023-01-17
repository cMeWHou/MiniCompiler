#include <WebAPI/WebInterface.h>

#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>

#include <General/Common.h>

static void WinsockStartup(WORD, LPWSADATA);
static SOCKET Socket(int, int, int);
static SOCKADDR_IN Address(string, int);
static void OpenSocket(TWebSocket*);
static void Bind(SOCKET, SOCKADDR_IN*);
static void Listen(SOCKET, int);
static TWebSocket* GetConnectedClient(TWebSocket*);
static void MemoryRelease(TWebInterface*);

TWebInterface *WebInterface(string serverIp, int serverPort) {
    TWebInterface *this = malloc(sizeof(TWebInterface));

    // CTR
    WinsockStartup(MAKEWORD(2, 0), &this->wsaData);

    this->serverSocket = new WebSocket();
    this->serverSocket->SetSocket(this->serverSocket, Socket(AF_INET, SOCK_STREAM, 0));
    this->serverSocket->SetAddress(this->serverSocket, Address(serverIp, serverPort));
    OpenSocket(this->serverSocket);

    this->clientSocket = GetConnectedClient(this->serverSocket);
    // ECTR

    return this;
}

static void WinsockStartup(WORD version, LPWSADATA wsaData) {
    if (WSAStartup(version, wsaData) != 0) {
        printf("WSAStartup() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static SOCKET Socket(int af, int type, int protocol) {
    SOCKET server;
    if ((server = socket(af, type, protocol)) == INVALID_SOCKET) {
        printf("socket() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
    return server;
}

static SOCKADDR_IN Address(string ip, int port) {
    SOCKADDR_IN address;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    return address;
}

static void Bind(SOCKET server, SOCKADDR_IN *address) {
    if (bind(server, (SOCKADDR*)address, sizeof(*address)) == SOCKET_ERROR) {
        printf("bind() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static void Listen(SOCKET server, int backlog) {
    if (listen(server, backlog) == SOCKET_ERROR) {
        printf("listen() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static void OpenSocket(TWebSocket *websocket) {
    Bind(websocket->socket, &websocket->address);
    Listen(websocket->socket, 0);
}

static TWebSocket *GetConnectedClient(TWebSocket* server) {
    TWebSocket *client = new WebSocket();
    if ((client->socket =
                 accept(server->socket, (SOCKADDR*)&client->address, &client->addressLength)) == INVALID_SOCKET) {
        printf("accept() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
    return client;
}

static void MemoryRelease(TWebInterface *this) {
    this->serverSocket->MemoryRelease(this->serverSocket);
    this->clientSocket->MemoryRelease(this->clientSocket);

    WSACleanup();

    free(this);

    this = __ZERO_PTR__;
}