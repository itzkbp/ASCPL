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
    
    List *init_list(size_t item_size);

    void list_push(List *list, void *item);
    
#endif