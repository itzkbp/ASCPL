#ifndef ASC_LOOKUP_H
    #define ASC_LOOKUP_H

    #include "List.h"
    #include "AST.h"

    #include "String.h"

    static AST *var_lookup(List *list, const char *name)
    {
        for(int i = 0; i < (int) list->size; i++)
        {
            AST *child_ast = (AST *) list->items[i];

            if(child_ast->type != AST_VARIABLE || !child_ast->name)
                continue;

            if(strcmp(child_ast->name, name) == 0)
                return child_ast;
        }

        return 0;
    }

#endif