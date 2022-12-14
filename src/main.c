#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "cexp.h"
#include "sockets.h"

int checkarg(int argc, char* argv[]);
int handleoptions();
void app_cleanup();

int main(int argc, char *argv[])
{
    signal(SIGINT, app_cleanup);
    list_add("Socket server", "sock:server", start_server);
    list_add("Socket client", "sock:client", clientstart);
    int result;

    printf("   _____                \n  / ____|               \n | |     _____  ___ __  \n | |    / _ \\ \\/ / '_ \\ \n | |___|  __/>  <| |_) |\n  \\_____\\___/_/\\_\\ .__/ \n                 | |    \n                 |_|    \n");

    // Check for argruments and if we can use them.
    result = checkarg(argc, argv);
    if (result == 0)
        return result;
    // If the app does not get args we will display a small options menu.
    result = handleoptions();
    app_cleanup();
    return result;
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

    PRINT_LINE("Option: [%s] chosen", data->name);

    return data->func_ptr != NULL ? data->func_ptr(NULL) : -1;
}

// Clean and exit the app.
void app_cleanup()
{
    clear_list(); // Clear the exp list.
    exit(0);
}
