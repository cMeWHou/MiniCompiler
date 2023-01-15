#include <Connector/Connector.h>

#include <stdlib.h>
#include <stdio.h>

#include <General/Common.h>

static void WinsockStartup(WORD, LPWSADATA);
static SOCKET Socket(int, int, int);
static SOCKET Accept(SOCKET, SOCKADDR*, int*);
static void Configure(SOCKADDR_IN *, string, int);
static void Bind(SOCKET, SOCKADDR *, int);
static void Listen(SOCKET, int);
static void CloseSocket(SOCKET);

static void MemoryRelease(TConnector*);

TConnector *Connector(string serverIp, int serverPort) {
    TConnector *this = malloc(sizeof(TConnector));

    this->Socket = Socket;
    this->Configure = Configure;
    this->Bind = Bind;
    this->Listen = Listen;
    this->WinsockStartup = WinsockStartup;
    this->Accept = Accept;
    this->CloseSocket = CloseSocket;

    // CTR
    this->WinsockStartup(MAKEWORD(2, 0), &this->wsaData);

    this->server = this->Socket(AF_INET, SOCK_STREAM, 0);
    this->Configure(&this->serverAddr, serverIp, serverPort);
    this->Bind(this->server, (SOCKADDR*)&this->serverAddr, sizeof(this->serverAddr));
    this->Listen(this->server, 0);

    this->clientAddrLength = sizeof(this->clientAddr);
    this->client = this->Accept(this->server, (SOCKADDR*)&this->clientAddr, &this->clientAddrLength);
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
    int server;
    if ((server = socket(af, type, protocol)) == INVALID_SOCKET) {
        printf("socket() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
    return server;
}

static void Configure(SOCKADDR_IN *address, string ip, int port) {
    address->sin_addr.s_addr = inet_addr(ip);
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
}

static void Bind(SOCKET server, SOCKADDR *address, int addressLength) {
    if (bind(server, address, addressLength) == SOCKET_ERROR) {
        printf("bind() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static void Listen(SOCKET server, int backlog){
    if (listen(server, backlog) == SOCKET_ERROR) {
        printf("listen() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static SOCKET Accept(SOCKET server, SOCKADDR* address, int* addressLength) {
    SOCKET client;
    if ((client = accept(server, address, addressLength)) == INVALID_SOCKET) {
        printf("accept() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
    return client;
}

static void CloseSocket(SOCKET server) {
    if (closesocket(server) == SOCKET_ERROR) {
        printf("closesocket() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static void MemoryRelease(TConnector* this) {
    this->CloseSocket(this->server);
    this->CloseSocket(this->client);
    WSACleanup();

    free(this);

    this = __ZERO_PTR__;
}