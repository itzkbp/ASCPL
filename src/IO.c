#include "include/IO.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"
#include "include/String.h"

FILE *tryOpening(const char *fileName, char *fileMode)
{
    FILE *fp = fopen(fileName, fileMode);

    if( fp == NULL)
    {
        printf("Cannot open file '%s'",fileName);
        perror("Error :");
        printf("\nExiting...\n");
        exit(1);
    }

    return fp;
}

char *asc_read_file(const char* fileName)
{
    char *line = NULL;
    size_t len;
    ssize_t read;

    FILE *fp = tryOpening(fileName, "r");

    char *buffer = (char *) calloc(1, sizeof(char));
    buffer[0] = '\0';

    while(( read = getline(&line, &len , fp) )!= EOF )
    {
        buffer = (char *) realloc(buffer, (strlen(buffer) +  strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);

    if(line)
        free(line);
    
    return buffer;
}