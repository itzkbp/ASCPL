#include "include/Optimizer.h"
#include "include/Lookup.h"
#include "include/BuiltIns.h"

#include "include/String.h"
#include "include/Stdlib.h"


Optimizer *init_optimizer()
{
    Optimizer *optimizer = (Optimizer *) calloc(1, sizeof(Optimizer));
    optimizer->object    = init_ast(AST_COMPOUND);

    init_builtins(optimizer->object->children);

    return optimizer;
}

AST *optimizer_optimize_compound(Optimizer *optimizer, AST *node, List *list)
{
    AST *compound = init_ast(AST_COMPOUND);

    for(uint i = 0; i < node->children->size; i++)
        list_push(compound->children, optimizer_optimize(optimizer, (AST *) node->children->items[i], list));

    return compound;
}

AST *optimizer_optimize_assignment(Optimizer *optimizer, AST *node, List *list)
{
    AST *new_variable   = init_ast(AST_ASSIGNMENT);

    new_variable->name  = node->name;
    new_variable->value = optimizer_optimize(optimizer, node->value, list);

    list_push(list, new_variable);

    return new_variable;
}

AST *optimizer_optimize_call(Optimizer *optimizer, AST *node, List *list)
{
    if(strcmp(node->name, mkstr("return"))==0)
        return node;
    
    AST *var = var_lookup(optimizer->object->children, node->name);
    
    if(var)
    {
        if(var->fptr)
        {
            return optimizer_optimize(optimizer, var->fptr(optimizer, var, node->value->children), list);
        }
    }

    return node;
}

AST *optimizer_optimize_variable(Optimizer *optimizer, AST *node, List *list)
{
    AST *var = var_lookup(optimizer->object->children, node->name);

    if(var)
        return var;

    return node;
}

AST *optimizer_optimize_function(Optimizer *optimizer, AST *node, List *list)
{
    AST *function      = init_ast(AST_FUNCTION);
    function->children = init_list(sizeof(AST *));
    function->value    = optimizer_optimize(optimizer, node->value, node->children);

    for(uint i = 0; i < node->children->size; i++)
        list_push(function->children, (AST *) optimizer_optimize(optimizer, (AST *) node->children->items[i], list));

    return function;
}

AST *optimizer_optimize_int(Optimizer *optimizer, AST *node, List *list)
{
    return node;
}

AST *optimizer_optimize_string(Optimizer *optimizer, AST *node, List *list)
{
    return node;
}

AST *optimizer_optimize_access(Optimizer *optimizer, AST *node, List *list)
{
    return node;
}


AST *optimizer_optimize(Optimizer *optimizer, AST *node, List *list)
{
    switch(node->type)
    {
        case AST_COMPOUND:   return optimizer_optimize_compound  (optimizer, node, list); break;
        case AST_ASSIGNMENT: return optimizer_optimize_assignment(optimizer, node, list); break;
        case AST_VARIABLE:   return optimizer_optimize_variable  (optimizer, node, list); break;
        case AST_CALL:       return optimizer_optimize_call      (optimizer, node, list); break;
        case AST_INT:        return optimizer_optimize_int       (optimizer, node, list); break;
        case AST_ACCESS:     return optimizer_optimize_access    (optimizer, node, list); break;
        case AST_FUNCTION:   return optimizer_optimize_function  (optimizer, node, list); break;
        case AST_STRING:     return optimizer_optimize_string    (optimizer, node, list); break;

        default: {
            printf("[Optimizer] :: Unexpected AST of type '%d'\n",node->type);
            exit(1);
        } break;
    }

    return node;
}