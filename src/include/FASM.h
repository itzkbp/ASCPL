#ifndef ASC_FASM_H
    #define ASC_FASM_H

    #include "AST.h"

    char *fasm_compound  (AST *ast, List *list);
    char *fasm_assignment(AST *ast, List *list);
    char *fasm_call      (AST *ast, List *list);
    char *fasm_variable  (AST *ast, List *list);
    char *fasm_int       (AST *ast, List *list);
    char *fasm_access    (AST *ast, List *list);
    char *fasm           (AST *ast, List *list);
    char *fasm_root      (AST *ast, List *list);

#endif