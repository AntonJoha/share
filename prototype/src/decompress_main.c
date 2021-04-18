#include <stdio.h>
#include <unistd.h>
#include "hiddenfile.h"
#include <stdlib.h>
int main(int argc, char *argv[], char*envp[])
{
    FILE* in = fopen(argv[0], "r");
    if(!in)
    {
        fprintf(stderr, "Error");
        exit(EXIT_FAILURE);
    }
    int out = decompressembeddedfile(in);
    printf("EXECUTING");
    out = fexecve(out, argv, envp);
    fprintf(stderr, "Something went wrong with fexecve");
}
