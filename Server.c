#include <Connector/Server.h>

#include <stdlib.h>
#include <stdio.h>

TServer* Server(DWORD (*Send)(LPVOID), DWORD (*Receive)(LPVOID), SOCKET* client) {
    TServer* this = malloc(sizeof(TServer));

    this->sendTask = CreateThread(NULL, 0, Send,
                                  client, 0, 0);
    this->recieveTask = CreateThread(NULL, 0, Receive,
                                     client, 0, 0);
    if (this->sendTask == NULL || this->recieveTask == NULL) {
        printf("Threads creation error: %d\n", WSAGetLastError());
    }
    WaitForSingleObject(this->sendTask, INFINITE);
    WaitForSingleObject(this->recieveTask, INFINITE);

    return this;
}