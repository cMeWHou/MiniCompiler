#include <WebAPI/Exchange.h>

#include <stdlib.h>
#include <stdio.h>

#include <General/Common.h>

#define BUFFER_SIZE 512

static void Start(TExchange*);
static DWORD WINAPI serverRecieve(LPVOID);
static DWORD WINAPI serverSend(LPVOID);
static void MemoryRelease(TExchange*);

TExchange* Exchange(TWebInterface* client) {
    TExchange* this = malloc(sizeof(TExchange));

    this->Start = Start;
    this->MemoryRelease = MemoryRelease;

    // CTR
    this->client = &client->clientSocket->socket;
    // ECTR

    return this;
}

static void Start(TExchange* this) {
    HANDLE sendTask = CreateThread(NULL, 0, serverSend,
                                  this->client, 0, 0);
    HANDLE receiveTask = CreateThread(NULL, 0, serverRecieve,
                                     this->client, 0, 0);
    if (sendTask == NULL || receiveTask == NULL) {
        printf("Threads creation error: %d\n", WSAGetLastError());
    }
    WaitForSingleObject(sendTask, INFINITE);
    WaitForSingleObject(receiveTask, INFINITE);
}

static DWORD WINAPI serverRecieve(LPVOID lpParam) {
    char buffer[BUFFER_SIZE] = {};
    SOCKET client = *(SOCKET *) lpParam;

    while (1) {
        if (recv(client, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
            printf("recv() - ERROR: %d\n", WSAGetLastError());
            exit(-1);
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    return 1;
}

static DWORD WINAPI serverSend(LPVOID lpParam) {
    char buffer[BUFFER_SIZE] = {};
    SOCKET client = *(SOCKET *) lpParam;

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        if (send(client, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
            printf("send() - ERROR: %d\n", WSAGetLastError());
            exit(-1);
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Thank you for using the application.");
            break;
        }
    }

    return 1;
}

static void MemoryRelease(TExchange* this) {
    free(this);

    this = __ZERO_PTR__;
}