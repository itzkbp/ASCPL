#ifndef ASC_UTILS_H
    #define ASC_UTILS_H

    #include "Stdio.h"
    #include "String.h"

    char *str_to_hex        (const char *inStr);
    char **str_to_hex_chunks(const char *inStr, int *no_of_chunks);

#endif