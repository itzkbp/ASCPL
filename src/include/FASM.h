#ifndef ASC_FASM_H
    #define ASC_FASM_H

    #include "AST.h"

    char *fasm_compound  (AST *ast);
    char *fasm_assignment(AST *ast);
    char *fasm_call      (AST *ast);
    char *fasm_variable  (AST *ast);
    char *fasm_int       (AST *ast);
    char *fasm           (AST *ast);
    char *fasm_root      (AST *ast);

#endif