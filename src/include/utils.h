#ifndef ASC_UTILS_H
    #define ASC_UTILS_H

    #include "Stdio.h"
    #include "String.h"

    #include "List.h"

    char *str_to_hex           (const char *inStr);
    List *str_to_hex_chunks    (const char *inStr);

    char *str_format           (const char *inStr);
    char str_to_escapeSequence (const char *inStr);

#endif