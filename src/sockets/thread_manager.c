#include <stdio.h>
#include "cexp.h"
#include "thread_manager.h"

int init_thread(int* clientfd, void *(*func) (void *))
{
    pthread_t thread;
    int thread_create_result = pthread_create(&thread, NULL, func, clientfd);
    if (thread_create_result == -1)
    {
        TRACE_ERROR("Could not create thread!");
        return thread_create_result;
    }
    PRINT_LINE("Init thread: %lu", thread);
    return 0;
}

