#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../sockets.h"
#include "thread_manager.h"

int server_sockfd;
struct sockaddr_in server_sockaddr;
bool b_listen = true;
char sName[64] = "Test server Linux\0";
struct net_data server_data;

void* thread_client_handler(void* arg);

int start_server()
{
    printf("   _____                \n  / ____|               \n | |     _____  ___ __  \n | |    / _ \ \/ / '_ \ \n | |___|  __/>  <| |_) |\n  \_____\___/_/\_\ .__/ \n                 | |    \n                 |_|    \n");
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0)
    {
        printf("ERROR: Could not create server socket!\n");
        return -1;
    }

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT_NUM);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(server_sockfd, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr));
    if (bind_result != 0)
    {
        printf("ERROR: Cannot bind to socket!\n");
        return -1;
    }

    while (b_listen)
    {
        printf("Waiting for a connection...\n");
        int listen_result = listen(server_sockfd, 1);
        if (listen_result == -1)
        {
            printf("ERROR: Could not listen. code: %i", errno);
            return -1;
        }
        int clientfd = accept(server_sockfd, NULL, NULL);
        if (clientfd == -1)
        {
            printf("ERROR: Could not accept client!");
            continue;
        }
        if (init_thread(&clientfd, thread_client_handler) == -1)
            printf("Warning: Could not establish connection with client!");
    }
    return 0;
}
int stop_server()
{
    return 0;
}

// Function used in thread to handle the connected client.
//TODO: Return a type with status, with message on why a value is returned.
void* thread_client_handler(void* arg)
{
    int client_fd = *(int*)arg;

    // Send data size to client.
    ssize_t sNameSize = sizeof(sName);
    uint32_t sDataSize = htonl(sNameSize);
    int sendResult = writeToSock(client_fd, &sDataSize, sizeof(uint32_t));
    if (sendResult == -1)// If we are not be able to send data, return so the thread can exit.
        return NULL;
    //char buff_recv[10];
    sendResult = writeToSock(client_fd, &sName, sNameSize);
    if (sendResult == -1)
        return NULL;


    char buff[50];
    // Wait for command data from client.
    for(;;)
    {
        printf("Listening to client for data!\n");
        int rec_result;
        rec_result = recv(client_fd, buff, sizeof(buff), 0);
        if (rec_result == -1)
        {
            printf("Warning: could not recieve data from client!\n");
            continue;
        }

        if (rec_result == 0)
        {
            printf("Client disconnected!\n");
            break;
        }
    }

    int close_result = close(client_fd);
    printf("Close network result: %i\n", close_result);
    return NULL;
}

