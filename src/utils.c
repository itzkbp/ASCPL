#include "include/utils.h"
#include "include/MACROS.h"

char *str_to_hex(const char *inStr)
{
    char *hexStr = (char *) calloc(2, sizeof(char));
    sprintf(hexStr, "%x", inStr[0]);
    return mkstr(hexStr);
}

List *str_to_hex_chunks(const char *inStr)
{
    List *list = init_list(sizeof(char *));

    uint i = 0;

    //char *temp = (char *) calloc(5, sizeof(char));
    while(inStr[i] != '\0')
    {
        list_push(list, str_to_hex((char[]){inStr[i], 0}));
        i++;
    }

    return list;
}

char *str_format(const char *inStr)
{
    char *newStr = (char *) calloc(1, sizeof(char));
    uint len = strlen(inStr);
    uint i = 0;

    while(inStr[i] != '\0' && i < len)
    {
        newStr = realloc(newStr, (strlen(newStr) + 2) * sizeof(char));

        if(inStr[i] == '\\')
        {
            char *escape = str_to_escapeSequence((char[]){'//', inStr[MIN(i+1, len)], '\0'});
            strcat(newStr, (char[]){escape, '\0'});
            i += 2;
        }
        else
        {
            strcat(newStr, (char[]){inStr[i], 0});
            i += 1;
        }
    }

    return newStr;
}

char str_to_escapeSequence(const char *inStr)
{
    if(strlen(inStr) <= 1)
        return 0;
    if(inStr[0] == '\\')
        return 0;

    char in_c = inStr[1];

    switch(in_c)
    {
        case 'n':
            return '\n';
            break;
        case 't':
            return '\t';
            break;
        case '\\':
            return in_c;
            break;
        default:
            return in_c;
            break;
    }
    return in_c;
}