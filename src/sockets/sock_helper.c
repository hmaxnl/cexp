#include "../sockets.h"

int writeToSock(int fd, void* data, ssize_t size)
{
    ssize_t dataSizeSend = 0;
    //dataSizeSend += send(fd, data, size, 0);
    while (dataSizeSend < size)
    {
        dataSizeSend += send(fd, (char*)data + dataSizeSend, size - dataSizeSend, 0);
        if (dataSizeSend == -1)
        {
            printf("Warning: Cannot send data!\n");
            return -1;
        }
    }
    return dataSizeSend;
}

// Do not check for buffer size!
int readFromSock(int fd, void* buff, ssize_t size)
{
    ssize_t dataRecv = 0;
    //dataRecv = recv(fd, buff, size, 0);
    while (dataRecv < size)
    {
        dataRecv += recv(fd, (char*)buff + dataRecv, size - dataRecv, 0);
        if (dataRecv == -1)
        {
            printf("Warning: Cannot receive data!\n");
            return -1;
        }
    }
    return dataRecv;
}
