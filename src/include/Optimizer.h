#ifndef ASC_OPTIMIZER_H
    #define ASC_OPTIMIZER_H

    #include "AST.h"

    typedef struct st_Optimizer{
        AST *object;
    } Optimizer;

    Optimizer *init_optimizer();

    AST *optimizer_optimize_compound  (Optimizer *optimizer, AST *node, List *list);
    AST *optimizer_optimize_assignment(Optimizer *optimizer, AST *node, List *list);
    AST *optimizer_optimize_call      (Optimizer *optimizer, AST *node, List *list);
    AST *optimizer_optimize_variable  (Optimizer *optimizer, AST *node, List *list);
    AST *optimizer_optimize_function  (Optimizer *optimizer, AST *node, List *list);
    AST *optimizer_optimize_int       (Optimizer *optimizer, AST *node, List *list);
    AST *optimizer_optimize_access    (Optimizer *optimizer, AST *node, List *list);

    AST *optimizer_optimize(Optimizer *optimizer, AST *node, List *list);

#endif