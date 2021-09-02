#ifndef ASC_OPTIMIZER_H
    #define ASC_OPTIMIZER_H

    #include "AST.h"

    typedef struct Optimizer{

    } Optimizer;

    Optimizer *init_optimizer();

    AST *optimizer_optimize(Optimizer *optimizer, AST *node, List *list);

#endif