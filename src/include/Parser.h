#ifndef ASC_PARSER_H
    #define ASC_PARSER_H

    #include "Lexer.h"
    #include "AST.h"

    typedef struct st_Parser
    {
        Lexer *lexer;
        Token *token;
    } Parser;

    Parser *init_parser       (Lexer *lexer);

    Token *parser_eat         (Parser *parser, int type);

    AST *parser_parse         (Parser *parser);
    AST *parser_parse_id      (Parser *parser);
    AST *parser_parse_list    (Parser *parser);
    AST *parser_parse_block   (Parser *parser);
    AST *parser_parse_exp     (Parser *parser);
    AST *parser_parse_int     (Parser *parser);
    AST *parser_parse_compound(Parser *parser);
    
#endif