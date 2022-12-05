#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../sockets.h"


void clientstart()
{
    int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in client_sockaddr;
    client_sockaddr.sin_family = AF_INET;
    client_sockaddr.sin_port = htons(PORT_NUM);
    client_sockaddr.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(client_sockfd, (struct sockaddr*) &client_sockaddr, sizeof(client_sockaddr));
    if (connection_status != 0)
    {
        printf("ERROR: Could not connect!\n");
        return;
    }

    ssize_t nextRecSize = 0;
    ssize_t recvRead = readFromSock(client_sockfd, &nextRecSize, sizeof(uint32_t));
    if (recvRead == -1)
    {
        printf("ERROR: Failed to receive data!\nErrno: %i", errno);
        return;
    }

    nextRecSize = ntohl(nextRecSize);
    char serverName[64];
    recvRead = readFromSock(client_sockfd, &serverName, nextRecSize);
    if (recvRead == -1)
        return;
    if (recvRead == 0)
    {
        printf("No data received!\n");
    }

    printf("Connected with: %s\n", serverName);

    for (;;)
    {
        char c = getchar();
        if (c == 'q')
            return;
    }
}