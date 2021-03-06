#include "include/ASC.h"
#include "include/Lexer.h"
#include "include/Token.h"
#include "include/Parser.h"
#include "include/IO.h"
#include "include/Optimizer.h"
#include "include/FASM.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"

void asc_compile(char *src, int assembly)
{
    Lexer *lexer = init_lexer(src);
    Parser *parser = init_parser(lexer);
    AST *root = parser_parse(parser);

    Optimizer *optimizer = init_optimizer();
    AST *optimized_root  = optimizer_optimize(optimizer, root, init_list(sizeof(AST *)));

    printf("\n\t###########################---------------------------------------------------------\n");
    printf(  "\t##  Generating Assembly  ## -> Wondering how COMPUTERS work? -> ASSEMBLY, maybe.   |");
    printf("\n\t###########################---------------------------------------------------------");
    printf("\n\tWOW! You got the ASSEMBLY equivalent of your .asc file right in here, take a look.\n\n");
    
    asc_write_file("./out.s", fasm_root(optimized_root, init_list(sizeof(AST *))) );
    system("as --32 ./out.s -o ./out.o");
    system("ld ./out.o -o ./output -m elf_i386");

    printf("\n\n\t Output File :: ./output\n\n");

    system("rm ./out.o");

    if(!assembly)
    {
        system("rm ./out.s");
        printf("\n\t#########################----------------------------------------------------------\n");
        printf(  "\t##  Removing Assembly  ## -> Use => [     --assembly    ] flag to prevent this.   |");
        printf("\n\t#########################----------------------------------------------------------\n\n");
    }
    // printf("%s\n",s);

    // printf("%p\n",root);
    // Token *token = 0;

    // while( (token = lexer_next_token(lexer))->type != TK_EOF )
    // {
    //     printf("%s\n",token_to_string(token));
    // }
}

void asc_compile_file(const char *fileName, int assembly)
{
    char *src = asc_read_file(fileName);
    asc_compile(src, assembly);
    free(src);
}