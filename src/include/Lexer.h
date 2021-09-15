#ifndef ASC_LEXER_H
    #define ASC_LEXER_H

    #include "Token.h"

    #include "Stdio.h"

    typedef struct st_Lexer
    {

        char *src;
        size_t src_size;
        char c;
        unsigned int i;
    } Lexer;
    
    Lexer *init_lexer           (char *src);

    void lexer_advance          (Lexer *lexer);
    void lexer_skip_whitespaces (Lexer *lexer);

    char lexer_peek             (Lexer *lexer, int offset);

    Token *lexer_advance_with   (Lexer *lexer, Token *token);
    Token *lexer_advance_current(Lexer *lexer, int type);
    Token *lexer_parse_id       (Lexer *lexer);
    Token *lexer_parse_int      (Lexer *lexer);
    Token *lexer_parse_string   (Lexer *lexer);
    Token *lexer_next_token     (Lexer *lexer);
#endif