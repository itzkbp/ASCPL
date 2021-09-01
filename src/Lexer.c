#include "include/Lexer.h"
#include "include/Token.h"
#include "include/MACROS.h"

#include "include/Stdlib.h"
#include "include/String.h"

#include <ctype.h>

Lexer *init_lexer(char *src)
{
    Lexer *lexer = (Lexer *) calloc(1, sizeof(Lexer));
    lexer->src      = src;
    lexer->src_size = strlen(src);
    lexer->i        = 0;
    lexer->c        = lexer->src[lexer->i];

    return lexer;
}

void lexer_advance(Lexer *lexer)
{
    if((lexer->i < lexer->src_size) && lexer->c != '\0')
    {
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}

char lexer_peek(Lexer *lexer, int offset)
{
    return lexer->src[MIN(lexer->i+offset, lexer->src_size)];
}

Token *lexer_advance_with(Lexer *lexer, Token *token)
{
    lexer_advance(lexer);
    return token;
}

Token *lexer_advance_current(Lexer *lexer, int type)
{
    char *value = (char *) calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    Token *token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

void lexer_skip_whitespaces(Lexer *lexer)
{
    while(lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
        lexer_advance(lexer);
}

Token *lexer_parse_id(Lexer *lexer)
{
    char *value =  (char *) calloc(1, sizeof(char));

    while(isalpha(lexer->c))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char) );
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TK_ID);
}

Token *lexer_parse_int(Lexer *lexer)
{
    char *value = (char *) calloc(1, sizeof(char));

    while(isdigit(lexer->c))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char) );
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TK_INT);
}

Token *lexer_next_token(Lexer *lexer)
{
    while(lexer->c != '\0')
    {
        lexer_skip_whitespaces(lexer);
        if(isalpha(lexer->c))
            return lexer_parse_id(lexer);

        if(isdigit(lexer->c))
            return lexer_parse_int(lexer);

        switch(lexer->c)
        {
            case '=': {
                if(lexer_peek(lexer, 1) != '>')
                    return lexer_advance_with(lexer, init_token("=", TK_EQUALS));

                return lexer_advance_with(lexer, lexer_advance_with(lexer, init_token("=>", TK_RARROW)));    
            } break;

            case '(': return lexer_advance_current(lexer, TK_LPAREN);
            case ')': return lexer_advance_current(lexer, TK_RPAREN);
            case '[': return lexer_advance_current(lexer, TK_LBRACKET);
            case ']': return lexer_advance_current(lexer, TK_RBRACKET);
            case ':': return lexer_advance_current(lexer, TK_COLON);
            case ',': return lexer_advance_current(lexer, TK_COMMA);
            case '<': return lexer_advance_current(lexer, TK_LT);
            case '>': return lexer_advance_current(lexer, TK_GT);
            case ';': return lexer_advance_current(lexer, TK_SEMICOLON);
            case '{': return lexer_advance_current(lexer, TK_LBRACE);
            case '}': return lexer_advance_current(lexer, TK_RBRACE);

            case '\0': break;

            default: {
                printf("[LEXER] :: Undentified Token '%c'\n",lexer->c);
                exit(1);
            }
        }
    }

    return init_token(0, TK_EOF);
}