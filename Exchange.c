#include <WebAPI/Exchange.h>

#include <stdlib.h>
#include <stdio.h>

#include <General/Common.h>

#define MESSAGE_SIZE 512

static string readMessage(TExchange *);
static void sendMessage(TExchange *, string);
static void MemoryRelease(TExchange *);
static int GetMessageSize(string);

TExchange *Exchange(TWebInterface *client) {
    TExchange *this = malloc(sizeof(TExchange));

    this->Read = readMessage;
    this->Send = sendMessage;

    this->MemoryRelease = MemoryRelease;

    // CTR
    this->client = &client->clientSocket->socket;
    // ECTR

    return this;
}

static string readMessage(TExchange *this) {
    string msg = (char[MESSAGE_SIZE]) {};
    SOCKET client = *(SOCKET *) this->client;

    while (1) {
        if (recv(client, msg, MESSAGE_SIZE, 0) == SOCKET_ERROR) {
            printf("recv() - ERROR: %d\n", WSAGetLastError());
            exit(-1);
        } else if (GetMessageSize(msg)) {
            break;
        }
    }

    return msg;
}

static void sendMessage(TExchange *this, string message) {
    string msg = (char[MESSAGE_SIZE]) {};
    memcpy(msg, message, MESSAGE_SIZE);
    SOCKET client = *(SOCKET *) this->client;

    if (send(client, msg, MESSAGE_SIZE, 0) == SOCKET_ERROR) {
        printf("send() - ERROR: %d\n", WSAGetLastError());
        exit(-1);
    }
}

static void MemoryRelease(TExchange *this) {
    free(this);

    this = __ZERO_PTR__;
}

static int GetMessageSize(string msg) {
    int size = 0;
    for (; msg[size] != '\n'; size++);
    return size;
}