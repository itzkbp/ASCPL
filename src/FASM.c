#include "include/FASM.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"
#include "include/String.h"

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

char *fasm_compound(AST *ast, List *list)
{
    char *value = (char *) calloc(1, sizeof(char));

    for(int i = 0; (int)i < ast->children->size; i++)
    {
        AST *child_ast = (AST *) ast->children->items[i];
        char *next_value = fasm(child_ast, list);
        value = realloc(value, (strlen(next_value) + 1) * sizeof(char) );
        strcat(value, next_value);
    }

    return value;
}

char *fasm_assignment(AST *ast, List *list)
{
    char *s = (char *) calloc(1, sizeof(char));

    if(ast->value->type == AST_FUNCTION)
    {
        const char *template = ".globl %s\n"
                               "%s:\n"
                               "pushl %%ebp\n"
                               "movl %%esp, %%ebp\n";
        s = realloc(s, (strlen(template)+ (strlen(ast->name)*2) +1) * sizeof(char));
        sprintf(s, template, ast->name, ast->name);

        AST *child_ast = ast->value;

        for(unsigned int i = 0; i < child_ast->children->size; i++)
        {
            AST *farg = (AST *) child_ast->children->items[i];
            AST *arg_variable = init_ast(AST_VARIABLE);
            arg_variable->name = farg->name;
            arg_variable->intValue = (int) child_ast->children->size + i;
            list_push(list, arg_variable);
        }
        
        char *child_ast_value = fasm(child_ast->value, list);
        s = realloc(s, (strlen(s) + strlen(child_ast_value) + 1) * sizeof(char));
        strcat(s, child_ast_value);
    }

    return s;
}

char *fasm_variable(AST *ast, List *list, int id)
{
    char *s = (char *) calloc(1, sizeof(char));

    if(ast->type == AST_INT)
    {
        const char *template = "$%d";
        s = realloc(s, (strlen(template) + 8) *sizeof(char));
        sprintf(s, template, ast->intValue);
    }
    else
    {
        const char *template = "%d(%%esp)";
        s = realloc(s, (strlen(template) + 8) *sizeof(char));
        sprintf(s, template, id);
    }
    
    return s;
}

char *fasm_call(AST *ast, List *list)
{
    char *s = (char *) calloc(1, sizeof(char));

    if(strcmp(ast->name, "return") == 0)
    {
        AST *first_arg = (AST *) ast->value->children->size ? ast->value->children->items[0] : (void *) 0;

        char *str = (char *) calloc(3, sizeof(char));
        strcpy(str, "$0");

        if(first_arg && first_arg->type == AST_VARIABLE)
        {
            char *str_s = fasm_variable(first_arg, list, 8);
            str = realloc(str, (strlen(str_s) + 1) *sizeof(str));
            strcpy(str,str_s);
            free(str_s);
        }

        const char *template = "movl %s, %%eax\n"
                               "movl %%ebp, %%esp\n"
                               "popl %%ebp\n\n"
                               "ret\n";

        char *ret_str = calloc(strlen(template) + 1, sizeof(char));
        sprintf(ret_str, template, str);

        s = realloc(s, (strlen(ret_str)+1) *sizeof(char) );
        strcat(s, ret_str);
    }

    return s;
}

char *fasm_int(AST *ast, List *list)
{
    return " int ";
}

char *fasm_access(AST *ast, List *list)
{
    char *s = (char *) calloc(1, sizeof(char));

    AST *first_arg = (AST *) ast->value->children->size ? ast->value->children->items[0] : (void *) 0;

    return s;
}

char *fasm_root(AST *ast, List *list)
{
    const char *section_text = ".section .text\n"
                               ".globl _start\n"
                               "_start:\n"
                               "pushl 0(\%esp)\n"
                               "pushl 4(\%esp)\n"            // not needed keeping for argv[n] 
                               "call main\n"
                               "addl $4, \%esp\n"             //adding 4 to esp, makes (esp) go back to its size
                               "movl \%eax, \%ebx\n"
                               "movl $1, \%eax\n"
                               "int $0x80\n\n";

    char *value = (char *) calloc((strlen(section_text) + 1), sizeof(char));
    strcpy(value, section_text);

    char *next_value = fasm(ast, list);
    value = realloc(value, (strlen(section_text) + strlen(next_value) + 1) *sizeof(char) );
    strcat(value, next_value);

    return value;
}

char *fasm(AST *ast, List *list)
{
    char *value = (char *) calloc(1, sizeof(char));
    char *next_value = 0;

    switch(ast->type)
    {
        case AST_COMPOUND:   next_value = fasm_compound(ast, list);    break;
        case AST_ASSIGNMENT: next_value = fasm_assignment(ast, list);  break;
        case AST_VARIABLE:   next_value = fasm_variable(ast, list, 0); break;
        case AST_CALL:       next_value = fasm_call(ast, list);        break;
        case AST_INT:        next_value = fasm_int(ast, list);         break;
        case AST_ACCESS:     next_value = fasm_access(ast, list);      break;

        default: {
            printf("[FASM] :: Unexpected AST of type '%d'\n",ast->type);
            exit(1);
        } break;
    }

    value = realloc(value, ( strlen(next_value) + 1 ) * sizeof(char));
    strcat(value, next_value);

    return value;
}