#include <stdio.h>
#include <unistd.h>
#include "hiddenfile.h"
int main(int argc, char *argv[], char*envp[])
{
    FILE* in = fopen(argv[1], "r");
    int out = decompressembeddedfile(in);
    out = fexecve(out, argv, envp);
    fprintf(stderr, "Something went wrong with fexecve");
}