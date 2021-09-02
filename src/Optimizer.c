#include "include/Optimizer.h"

#include "include/Stdlib.h"

Optimizer *init_optimizer()
{
    Optimizer *optimizer = (Optimizer *) calloc(1, sizeof(Optimizer));

    return optimizer;
}

AST *optimizer_optimize(Optimizer *optimizer, AST *node, List *list)
{
    return node;
}