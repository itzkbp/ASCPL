#include "include/utils.h"

char *str_to_hex(const char *inStr)
{
    uint len     = strlen(inStr);
    char *hexStr = (char *) calloc(len * 4, sizeof(char));

    for(uint i = 0; i < len; i++)
    {
        char *newStr = (char *) calloc(4, sizeof(char));
        sprintf(newStr, "%x", inStr[len-1-i]);
        strcat(hexStr, newStr);
        free(newStr);
    }

    return hexStr;
}

char **str_to_hex_chunks(const char *inStr, int *no_of_chunks)
{
    uint len = strlen(inStr);
    uint n_chunks = (len/4) + 1; 
    *no_of_chunks = n_chunks;

    char **strlist = (char **) calloc(n_chunks * 5, sizeof(char));

    for(uint i = 0; i < n_chunks; i++)
    {
        char *chunkstr = mkstr(inStr + (i*4));
        chunkstr = (char *) realloc(chunkstr, 4);
        chunkstr[4] = 0;

        char *hexStr = str_to_hex(chunkstr);

        strlist[i] = hexStr;
    }

    return strlist;
}