#ifndef ASC_AST_H
    #define ASC_AST_H

    #include "List.h"

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
            AST_NO_OPERATION,
        } type;

        struct st_AST *value;
        int dataType;
        int intValue;
        List *children;
        char *name;
    } AST;

    AST *init_ast       (int type);
    int  typeName_to_Int(const char *name);
    
#endif