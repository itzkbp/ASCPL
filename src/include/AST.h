#ifndef ASC_AST_H
    #define ASC_AST_H

    #include "List.h"

    struct st_Optimizer;

    typedef struct st_AST
    {
        enum en_AST {
            AST_COMPOUND,
            AST_FUNCTION,
            AST_INT,
            AST_DEF_TYPE,
            AST_VARIABLE,
            AST_STATEMENT,
            AST_CALL,
            AST_ACCESS,
            AST_ASSIGNMENT,
            AST_STRING,
            AST_NO_OPERATION,
        } type;

        struct st_AST *value;
        int dataType;
        int intValue;
        char *stringValue;
        List *children;
        char *name;

        struct st_AST *(*fptr)(struct st_Optimizer *optimizer, struct st_AST *node, List *list);
        // struct st_AST *(st_AST::*fptr) ...
        
    } AST;

    AST *init_ast       (int type);
    int  typeName_to_Int(const char *name);
    
#endif