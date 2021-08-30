#include "include/ASC.h"
#include "include/Lexer.h"
#include "include/Token.h"
#include "include/Parser.h"
#include "include/IO.h"
#include "include/FASM.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"

void asc_compile(char *src)
{
    Lexer *lexer = init_lexer(src);
    Parser *parser = init_parser(lexer);
    AST *root = parser_parse(parser);

    char *s = fasm_root(root);

    asc_write_file("./bin/out.s",s);
    // printf("%s\n",s);

    // printf("%p\n",root);
    // Token *token = 0;

    // while( (token = lexer_next_token(lexer))->type != TK_EOF )
    // {
    //     printf("%s\n",token_to_string(token));
    // }
}

void asc_compile_file(const char *fileName)
{
    char *src = asc_read_file(fileName);
    asc_compile(src);
    free(src);
}