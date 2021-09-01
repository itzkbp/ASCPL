#include "include/Parser.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"
#include "include/String.h"

Parser *init_parser(Lexer *lexer)
{
    Parser *parser = (Parser *) calloc(1, sizeof(Parser));

    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}

Token *parser_eat(Parser *parser, int type)
{
    if(parser->token->type != type)
    {
        printf("[Parser] :: Unexpected Token %s.\nExpected %s",token_to_string(parser->token),token_type_to_string(type));
        exit(1);
    }
    parser->token = lexer_next_token(parser->lexer);
    return parser->token;
}

AST *parser_parse(Parser *parser)
{
    return parser_parse_compound(parser);
}

AST *parser_parse_id(Parser *parser)
{
    char *value = calloc( (strlen(parser->token->value) + 1) ,sizeof(char));
    strcpy(value, parser->token->value);
    parser_eat(parser, TK_ID);

    if(parser->token->type == TK_EQUALS)
    {
        parser_eat(parser, TK_EQUALS);
        AST *ast = init_ast(AST_ASSIGNMENT);
        ast->name = value;
        ast->value = parser_parse_exp(parser);
        return ast;
    }

    AST *ast = init_ast(AST_VARIABLE);
    ast->name = value;

    if(parser->token->type == TK_COLON)
    {
        parser_eat(parser, TK_COLON);

        while(parser->token->type == TK_ID)
        {
            ast->dataType = typeName_to_Int(parser->token->value);
            parser_eat(parser, TK_ID);
    
            if(parser->token->type == TK_LT)
            {
                parser_eat(parser, TK_LT);
                ast->dataType += typeName_to_Int(parser->token->value);
                parser_eat(parser, TK_ID);
                parser_eat(parser, TK_GT);
            }
        }
    }
    else
    {
        if(parser->token->type == TK_LPAREN)
        {
            ast->type = AST_CALL;
            ast->value = parser_parse_list(parser);
        }
        else if(parser->token->type == TK_LBRACKET)
        {
            ast->type = AST_ACCESS;
            ast->value = parser_parse_list(parser);
        }
    }

    return ast;
}

AST *parser_parse_list(Parser *parser)
{
    unsigned int isBracket = (parser->token->type == TK_LBRACKET);

    parser_eat(parser, (isBracket) ? TK_LBRACKET : TK_LPAREN);

    AST *compound = init_ast(AST_COMPOUND);
    list_push(compound->children, parser_parse_exp(parser));

    while(parser->token->type == TK_COMMA)
    {
        parser_eat(parser, TK_COMMA);
        list_push(compound->children, parser_parse_exp(parser));
    }

    parser_eat(parser, (isBracket) ? TK_RBRACKET : TK_RPAREN);

    if(parser->token->type == TK_COLON)
    {
        parser_eat(parser, TK_COLON);

        while(parser->token->type == TK_ID)
        {
            compound->dataType = typeName_to_Int(parser->token->value);
            parser_eat(parser, TK_ID);
    
            if(parser->token->type == TK_LT)
            {
                parser_eat(parser, TK_LT);
                compound->dataType += typeName_to_Int(parser->token->value);
                parser_eat(parser, TK_ID);
                parser_eat(parser, TK_GT);
            }
        }
    }

    if(parser->token->type == TK_RARROW)
    {
        parser_eat(parser, TK_RARROW);
        compound->type = AST_FUNCTION;
        compound->value = parser_parse_compound(parser);
    }

    return compound;
}

AST *parser_parse_block(Parser *parser)
{
    parser_eat(parser, TK_LBRACE);

    AST *ast = init_ast(AST_COMPOUND);

    while(parser->token->type != TK_RBRACE)
    {
        list_push(ast->children, parser_parse_exp(parser));
    }
    parser_eat(parser,TK_RBRACE);

    return ast;
}

AST *parser_parse_exp(Parser *parser)
{
    switch(parser->token->type)
    {
        case TK_ID:     return parser_parse_id(parser);
        case TK_LPAREN: return parser_parse_list(parser);
        case TK_INT:    return parser_parse_int(parser);

        default: {
            printf("[Parser] :: Unexpected Token %s.\n", token_to_string(parser->token));
            exit(1);
        } break;
    }
}

AST *parser_parse_int(Parser *parser)
{
    int intVal = atoi(parser->token->value);
    parser_eat(parser, TK_INT);

    AST *ast = init_ast(AST_INT);
    ast->intValue = intVal;

    return ast;
}

AST *parser_parse_compound(Parser *parser)
{
    int shouldClose = 0;
    if(parser->token->type == TK_LBRACE)
    {
        parser_eat(parser, TK_LBRACE);
        shouldClose = 1;
    }
    AST *compound = init_ast(AST_COMPOUND);

    while((parser->token->type != TK_EOF) && (parser->token->type != TK_RBRACE))
    {
        list_push(compound->children, parser_parse_exp(parser));

        if(parser->token->type == TK_SEMICOLON)
            parser_eat(parser, TK_SEMICOLON);
    }

    if(shouldClose)
        parser_eat(parser, TK_RBRACE);

    return compound;
}