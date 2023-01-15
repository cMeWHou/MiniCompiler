#include <Socket/Server.h>

#include <stdlib.h>
#include <stdio.h>

#include <General/Common.h>

static void Start(TServer*);
static void MemoryRelease(TServer*);

TServer* Server(DWORD (*Send)(LPVOID), DWORD (*Receive)(LPVOID), SOCKET* client) {
    TServer* this = malloc(sizeof(TServer));

    this->Start = Start;
    this->MemoryRelease = MemoryRelease;

    // CTR
    this->Send = Send;
    this->Receive = Receive;
    this->client = client;

    this->Start(this);
    // ECTR

    return this;
}

static void Start(TServer* this) {
    this->sendTask = CreateThread(NULL, 0, this->Send,
                                  this->client, 0, 0);
    this->recieveTask = CreateThread(NULL, 0, this->Receive,
                                     this->client, 0, 0);
    if (this->sendTask == NULL || this->recieveTask == NULL) {
        printf("Threads creation error: %d\n", WSAGetLastError());
    }
    WaitForSingleObject(this->sendTask, INFINITE);
    WaitForSingleObject(this->recieveTask, INFINITE);
}

static void MemoryRelease(TServer* this) {
    free(this);

    this = __ZERO_PTR__;
}