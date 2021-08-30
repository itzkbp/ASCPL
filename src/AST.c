#include "include/AST.h"

#include "include/Stdlib.h"
#include "include/String.h"

AST *init_ast(int type)
{
    AST *ast = (AST *) calloc(1, sizeof(AST));
    ast->type = type;

    if(type == AST_COMPOUND)
        ast->children = init_list(sizeof(AST *));

    return ast;
}

int typeName_to_Int(const char *name)
{
    int t = 0;
    size_t len = strlen(name);

    for(unsigned int i = 0; i < len; i++)
        t += (int)name[i];

    return t;
}