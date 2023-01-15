// Here you can modify Send/Receive algorithms

#include <Socket/Exchange.h>

#include <stdio.h>

DWORD WINAPI serverRecieve(LPVOID lpParam) {
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

DWORD WINAPI serverSend(LPVOID lpParam) {
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