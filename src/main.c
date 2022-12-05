#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "sockets.h"


static void sig_handler();

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_handler);
    if (argc == 2)
    {
        if (strcmp(argv[1], "server") == 0)
        {
            return start_server();
        }
        if (strcmp(argv[1], "client") == 0)
        {
            clientstart();
            return 0;
        }
    }

    printf("None or too much arguments passed!\n");
    return 0;
}

// Handle the signal to exit the app!
static void sig_handler()
{
    stop_server();
    exit(0);
}
