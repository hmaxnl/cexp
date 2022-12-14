#ifndef CEXP_H
#define CEXP_H
#include <stdio.h>
#include <ctype.h>


struct exp_data{
    char* name;
    char* command;
    int (*func_ptr) (void*);
};
// Exp list functions
void list_add(char* name, char* command, int (*exp_func) (void*));
void print_list_items();
struct exp_data* get_from_list(int index);
void clear_list();

// Tracing
#define PRINT_LINE(msg, args...) fprintf(stdout, #msg "\n", ##args)
#define TRACE_WARN(msg, args...) fprintf(stdout, "[Warning]: " #msg "\n", ##args)
#define TRACE_ERROR(msg, args...) fprintf(stderr, "[ERROR]: " #msg "\n", ##args)

#endif
