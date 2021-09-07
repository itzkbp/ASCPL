#include "include/BuiltIns.h"

#include "include/String.h"


AST *fptr_print(Optimizer *optimizer, AST *node, List *list)
{
    AST *ast = init_ast(AST_STRING);
    const char *template = "movl $4, \%eax\n"   //syscall write
                           "movl $1, \%ebx\n"   //stdout
                           "movl $0, \%ecx\n"   //buffer
                           "movl $0, \%edx\n"   //size
                           "int $0x80\n";

    ast->stringValue = mkstr(template);

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