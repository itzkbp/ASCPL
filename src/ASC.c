#include "include/ASC.h"
#include "include/Lexer.h"
#include "include/Token.h"
#include "include/Parser.h"
#include "include/IO.h"
#include "include/FASM.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"

void asc_compile(char *src, int assembly)
{
    Lexer *lexer = init_lexer(src);
    Parser *parser = init_parser(lexer);
    AST *root = parser_parse(parser);

    printf("\n\t###########################---------------------------------------------------------\n");
    printf(  "\t##  Generating Assembly  ## -> Wondering how COMPUTERS work? -> ASSEMBLY, maybe.   |");
    printf("\n\t###########################---------------------------------------------------------");
    printf("\n\tWOW! You got the ASSEMBLY equivalent of your .asc file right inside bin, take a look.\n");

    asc_write_file("./bin/out.s",fasm_root(root));

    system("as --32 ./bin/out.s -o ./bin/out.o");
    system("ld ./bin/out.o -o ./bin/output -m elf_i386");

    printf("\n\n\t Output File :: ./bin/output\n\n");

    system("rm ./bin/out.o");

    if(!assembly)
    {
        system("rm ./bin/out.s");
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