#include "hidefile.h"
#include "compression.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define path "/dev/shm/xxxx"
int hidefile(FILE* target, FILE* tohide)
{
    
    //Get a psuedo random filepath
#define STARTOFFSET 9
/*
    char path[20];
    //Just to get some random value
    unsigned long value = (unsigned long) &path;
    strcpy(path, "/dev/shm/XXXXX");
    for (int i = STARTOFFSET; i < STARTOFFSET + 5; ++i)
    {
        //Magic value for no real reason
        path[i] -= (value % (i%13));
    }
*/
#undef STARTOFFSET

    FILE* temp = fopen(path, "w");

    if (compress(tohide, temp))
    {
        fprintf(stderr, "Something went wrong with the compression\nEnding...\n");
        exit(EXIT_FAILURE);
    }

    fclose(tohide);
    fclose(temp);
    fseek(target, 0, SEEK_END);
    temp = fopen(path, "r");
    unlink(path);   

    unsigned long count = 0;
    char c;
    fprintf(target, "%c", 0);
    while(1)
    {
        if (fscanf(temp, "%c", &c) == EOF)
        {
            break;
        }
        fprintf(target, "%c", c);
        ++count;
    }

    fprintf(target, "%lu", count);
}
