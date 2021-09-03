#ifndef ASC_BUILTINS_H
    #define ASC_BUILTINS_H

    #include "Optimizer.h"


    AST *fptr_print(Optimizer *optimizer, AST *node, List *list);

    void builtins_register_fptr(List *list,const char *name, AST *(*fptr)(Optimizer *optimizer, AST *node, List *list));

    void init_builtins(List *list);

#endif