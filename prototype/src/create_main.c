#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CASE_HELP printf("usage: elfcomp [-h] <in> <out>\n\nThe given file is compressed with Bzip2.\nThe compressed file is then appended to a decompresser, also made with the help of bzip that decompress and then executes.\n The compressed file will execute like it would if it wastn't compressed, i.e the same environment variables and arguments are going to get passed along.\n\noptional arguments: \n  -h, -h\t\tshow this help message and exit\n");


int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-h"))
        {
            CASE_HELP;
            return 0;
        }
    }
    if (argc < 3)
    {
        fprintf(stderr, "Too few argument");
        CASE_HELP;
        return -1;
    }
    char tosystem[256];

    sprintf(tosystem, "cp frame %s", argv[2]);
    system(tosystem);
    sprintf(tosystem, "compress %s %s", argv[1], argv[2]);
    system(tosystem);
    printf("Done compressing.");
}