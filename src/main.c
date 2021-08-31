#include "include/ASC.h"

#include "include/Stdio.h"
#include "include/Stdlib.h"
#include "include/String.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("\n\t\t#####################--------------------------------------------\n");
        printf(  "\t\t##  No input file  ## ---->    use =>      ./asc fileName.asc    |");
        printf("\n\t\t#####################--------------------------------------------\n\n");
        printf("\t\tUse the file in examples. e.g       .asc ./examples/ex-1.asc\n\n");

        return 1;
    }
    system("mkdir bin");
    asc_compile_file(argv[1], argc > 2 && (strcmp(argv[2], "--assembly") == 0) ? 1 : 0);
    return 0;
}