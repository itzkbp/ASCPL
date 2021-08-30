#include "include/ASC.h"

#include "include/Stdio.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No input file");
        return 1;
    }

    asc_compile_file(argv[1]);
    return 0;
}