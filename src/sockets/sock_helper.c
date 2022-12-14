#include "cexp.h"
#include "sockets.h"

int writeToSock(int fd, void* data, ssize_t size)
{
    ssize_t dataSizeSend = 0;
    //dataSizeSend += send(fd, data, size, 0);
    while (dataSizeSend < size)
    {
        dataSizeSend += send(fd, (char*)data + dataSizeSend, size - dataSizeSend, 0);
        if (dataSizeSend == -1)
        {
            TRACE_WARN("Cannot send data!");
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
            TRACE_WARN("Cannot receive data!");
            return -1;
        }
    }
    return dataRecv;
}
