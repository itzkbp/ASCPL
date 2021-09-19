#include "include/BuiltIns.h"
#include "include/utils.h"

#include "include/String.h"


AST *fptr_print(Optimizer *optimizer, AST *node, List *list)
{
    AST *ast = init_ast(AST_STRING);

    AST *first_arg = list->size ? (AST *) optimizer_optimize(optimizer, list->items[0], list) : (AST *) 0;
    char *instruc  = first_arg ? first_arg->stringValue : 0;
    char *hexStr = 0;

    int no_of_chunks = 0;

    if(first_arg)
    {
        if(first_arg->type == AST_INT)
        {
            instruc = (char *) calloc(128, sizeof(char));
            sprintf(instruc, "%d", first_arg->intValue);
        }

        List *list = str_to_hex_chunks(instruc);
        no_of_chunks = (int) list->size;

        char *strpush = (char *) calloc(1, sizeof(char));
        const char *pushtemplate = "pushl $0x%s\n";

        for(int i = 0; i < no_of_chunks; i++)
        {
            char *pushhex = (char *) list->items[no_of_chunks-i-1];
            char *push = (char *) calloc(strlen(pushhex) + strlen(pushtemplate) + 1, sizeof(char));
            sprintf(push, pushtemplate, pushhex);
            strpush = realloc(strpush, (strlen(strpush) + strlen(push) + 1)*sizeof(char));
            strcat(strpush, push);
            free(pushhex);
            free(push);
        }

        hexStr = strpush;
    }

    const char *template = "movl $4, %%eax\n"   //syscall write
                           "movl $1, %%ebx\n"   //stdout
                           "%s"
                           "movl %%esp, %%ecx\n"
                           "addl $%d, %%esp\n"
                           "movl $%d, %%edx\n"   //size
                           "int $0x80\n";

    char *asmbly = (char *) calloc(strlen(template) + (hexStr ? strlen(hexStr) : 0) + 1, sizeof(char));
    sprintf(asmbly, template, (hexStr ? hexStr : "$0"), no_of_chunks * 4, no_of_chunks * 4);
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