#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H
#include <pthread.h>
#include "../sockets.h"

int init_thread(int* clientfd, void *(*func) (void *));

#endif
