#include "include/BuiltIns.h"
#include "include/utils.h"

#include "include/String.h"


AST *fptr_print(Optimizer *optimizer, AST *node, List *list)
{
    AST *ast = init_ast(AST_STRING);

    AST *first_arg = list->size ? (AST *) list->items[0] : (AST *) 0;
    char *instruc  = (char *) calloc(128, sizeof(char));
    char *hexStr = 0;

    if(first_arg)
    {
        sprintf(instruc, "%d", first_arg->intValue);
        hexStr = str_to_hex(instruc);
    }

    const char *template = "movl $4, %%eax\n"   //syscall write
                           "movl $1, %%ebx\n"   //stdout
                           "pushl $0x%s\n"
                           "movl %%esp, %%ecx\n"
                           "movl $%d, %%edx\n"   //size
                           "int $0x80\n";

    char *asmbly = (char *) calloc(strlen(template) + (hexStr ? strlen(hexStr) : 0) + 1, sizeof(char));
    sprintf(asmbly, template, (hexStr ? hexStr : "$0"), hexStr ? strlen(hexStr) * 2: 0);
    ast->stringValue = asmbly;

    free(hexStr);

    return ast;
}

void builtins_register_fptr(List *list,const char *name, AST *(*fptr)(Optimizer *optimizer, AST *node, List *list))
{
    AST *fptr_print_var  = init_ast(AST_VARIABLE);
    fptr_print_var->name = mkstr(name);
    fptr_print_var->fptr = fptr;

    list_push(list, fptr_print_var);
}

void init_builtins(List *list)
{
    builtins_register_fptr(list, "print", fptr_print);
}