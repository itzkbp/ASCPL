#ifndef ASC_LIST_H
    #define ASC_LIST_H

    #include "Stdio.h"
    #include "Stdlib.h"

    typedef struct st_List
    {
        void **items;
        size_t size;
        size_t item_size;
    } List;
    
    List *init_list(size_t item_size)
    {
        List *list = (List *) calloc(1, sizeof(List));
        list->size  = 0;
        list->item_size = item_size;
        list->items = 0;

        return list;
    }

    void list_push(List *list, void *item)
    {
        list->size += 1;

        if(!list->items)
            list->items = calloc(1, list->item_size);
        else
            list->items = realloc(list->items, (list->size * list->item_size));
    
        list->items[list->size - 1] = item;
    }
    
#endif