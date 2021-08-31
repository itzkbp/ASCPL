#include "include/FASM.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"
#include "include/String.h"

char *fasm_compound(AST *ast)
{
    char *value = (char *) calloc(1, sizeof(char));

    for(int i = 0; (int)i < ast->children->size; i++)
    {
        AST *child_ast = (AST *) ast->children->items[i];
        char *next_value = fasm(child_ast);
        value = realloc(value, (strlen(next_value) + 1) * sizeof(char) );
        strcat(value, next_value);
    }

    return value;
}

char *fasm_assignment(AST *ast)
{
    char *s = (char *) calloc(1, sizeof(char));

    if(ast->value->type == AST_FUNCTION)
    {
        const char *template = ".globl %s\n"
                               "%s:\n"
                               "pushl %%esp\n"
                               "movl %%esp, %%ebp\n";
        s = realloc(s, (strlen(template)+ (strlen(ast->name)*2) +1) * sizeof(char));
        sprintf(s, template, ast->name, ast->name);

        AST *child_ast = ast->value;
        
        char *child_ast_value = fasm(child_ast->value);
        s = realloc(s, (strlen(s) + strlen(child_ast_value) + 1) * sizeof(char));
        strcat(s, child_ast_value);
    }

    return s;
}

char *fasm_variable(AST *ast)
{
    return " variable ";
}

char *fasm_call(AST *ast)
{
    char *s = (char *) calloc(1, sizeof(char));

    if(strcmp(ast->name, "return") == 0)
    {
        AST *first_arg = (AST *) ast->value->children->size ? ast->value->children->items[0] : (void *) 0;

        const char *template = "movl %%ebp, %%esp\n"
                               "popl %%ebp\n\n"
                               "movl $%d, %%eax\n"
                               "ret\n";

        char *ret_str = calloc(strlen(template) + 1, sizeof(char));
        sprintf(ret_str, template, (first_arg ? first_arg->intValue : 0) );

        s = realloc(s, (strlen(ret_str)+1) *sizeof(char) );
        strcat(s, ret_str);
    }

    return s;
}

char *fasm_int(AST *ast)
{
    return " int ";
}

char *fasm_root(AST *ast)
{
    const char *section_text = ".section .text\n"
                               ".globl _start\n"
                               "_start:\n"
                               "push 0(\%esp)\n"
                               "call main\n"
                               "addl $4, \%esp\n"             //adding 4 to esp, makes (esp) go back to its size
                               "movl \%eax, \%ebx\n"
                               "movl $1, \%eax\n"
                               "int $0x80\n\n";

    char *value = (char *) calloc((strlen(section_text) + 1), sizeof(char));
    strcpy(value, section_text);

    char *next_value = fasm(ast);
    value = realloc(value, (strlen(section_text) + strlen(next_value) + 1) *sizeof(char) );
    strcat(value, next_value);

    return value;
}

char *fasm(AST *ast)
{
    char *value = (char *) calloc(1, sizeof(char));
    char *next_value = 0;

    switch(ast->type)
    {
        case AST_COMPOUND:   next_value = fasm_compound(ast);   break;
        case AST_ASSIGNMENT: next_value = fasm_assignment(ast); break;
        case AST_VARIABLE:   next_value = fasm_variable(ast);   break;
        case AST_CALL:       next_value = fasm_call(ast);       break;
        case AST_INT:        next_value = fasm_int(ast);        break;

        default: {
            printf("[FASM] :: Unexpected AST of type '%d'\n",ast->type);
            exit(1);
        } break;
    }

    value = realloc(value, ( strlen(next_value) + 1 ) * sizeof(char));
    strcat(value, next_value);

    return value;
}