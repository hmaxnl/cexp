#include <stdio.h>
#include "thread_manager.h"

int init_thread(int* clientfd, void *(*func) (void *))
{
    pthread_t thread;
    int thread_create_result = pthread_create(&thread, NULL, func, clientfd);
    if (thread_create_result == -1)
    {
        printf("ERROR: Could not create thread!\n");
        return thread_create_result;
    }
    printf("Init thread: %lu\n", thread);
    return 0;
}

