#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "cexp.h"
#include "sockets.h"

int checkarg(int argc, char* argv[]);
int handleoptions();
static void sig_handler();

int main(int argc, char *argv[])
{
    list_add("Socket server", "sock:server", start_server);
    list_add("Socket client", "sock:client", clientstart);
    printf("   _____                \n  / ____|               \n | |     _____  ___ __  \n | |    / _ \\ \\/ / '_ \\ \n | |___|  __/>  <| |_) |\n  \\_____\\___/_/\\_\\ .__/ \n                 | |    \n                 |_|    \n");
    signal(SIGINT, sig_handler);
    int argresult = checkarg(argc, argv);
    if (argresult == 0) // If checkarg returns 0 that means it succesfully handled the argruments.
        return argresult;
    return handleoptions(); // If the app does not get args we will display a small options menu.
}
int checkarg(int argc, char* argv[])
{
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
    return -1;
}

int handleoptions()
{
    PRINT_LINE("Choose a option:");
    print_list_items();
    int index;
    if (scanf("%d", &index) == 0)
    {
        TRACE_WARN("No valid option selected!");
        return -1;
    }

    struct exp_data* data = get_from_list(index);
    if (data == NULL)
    {
        TRACE_ERROR("Could not get required data from list!");
        return -1;
    }

    PRINT_LINE("Option: %s choosen", data->name);

    return data->func_ptr != NULL ? data->func_ptr(NULL) : -1;
}

// Handle the signal to exit the app!
static void sig_handler()
{
    clear_list(); // Clear the exp list.
    exit(0);
}
