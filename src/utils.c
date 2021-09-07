#include "include/utils.h"

char *str_to_hex(const char *inStr)
{
    uint len     = strlen(inStr);
    char *hexStr = (char *) calloc(len * 4, sizeof(char));

    for(uint i = 0; i < len; i++)
    {
        char *newStr = (char *) calloc(4, sizeof(char));
        sprintf(newStr, "%x", inStr[i]);
        strcat(hexStr, newStr);
        free(newStr);
    }

    return hexStr;
}