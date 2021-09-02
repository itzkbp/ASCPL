#ifndef ASC_STRING_H
    #define ASC_STRING_H
    #include <string.h>

    #include "Stdlib.h"

    static char *mkstr(const char *str)
    {
        char *outstr = (char *) calloc(strlen(str) + 1, sizeof(char));
        strcpy(outstr, str);

        return outstr;
    }

#endif