#ifndef SOCKETS_H
#define SOCKETS_H
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT_NUM 42069

struct net_data
{
    char sName[100];
};

int clientstart();
int start_server();


int writeToSock(int fd, void* data, ssize_t size);
int readFromSock(int fd, void* buff, ssize_t size);

#endif
