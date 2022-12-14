#include "stdlib.h"
#include "cexp.h"

#define INCREMENT_SIZE 5


int alloc_list();
int increment_list();

static int list_index_count = 0;
static int list_index_total = 0;
static struct exp_data* list = NULL;

void list_add(char* name, char* command, int (*exp_func) (void*))
{
    if (alloc_list() != 0)
    { TRACE_ERROR("Unable to allocate memory!"); return; }
    list[list_index_count].name = name;
    list[list_index_count].command = command;
    list[list_index_count].func_ptr = exp_func;
    list_index_count++;
}

int alloc_list()
{
    if (list == NULL)
    {
        list = (struct exp_data*)calloc(sizeof(struct exp_data), INCREMENT_SIZE);
        if (list == NULL)
            return -1;
        list_index_total += INCREMENT_SIZE;
    }
    if (list_index_total <= list_index_count)
        return increment_list();
    return 0;
}
int increment_list()
{
    list_index_total += INCREMENT_SIZE;
    list = realloc(list, list_index_total * sizeof(struct exp_data));
    if (list == NULL)
        return -1;
    return 0;
}
void print_list_items()
{
    for (int i = 0; i < list_index_count; i++)
    {
        PRINT_LINE("%i. %s", i, list[i].name);
    }
}
struct exp_data* get_from_list(int index)
{
    if (index > list_index_count)
        return NULL;
    return &list[index];
}

void clear_list()
{
    if (list != NULL)
        free(list);
    return;
}
