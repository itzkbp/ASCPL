#ifndef ASC_IO_H
    #define ASC_IO_H
    
    #include "Stdio.h"

    FILE *tryOpening    (const char *fileName, char *fileMode);
    char *asc_read_file (const char* fileName);
    void  asc_write_file(const char* fileName, char *outString);
    
#endif