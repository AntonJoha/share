#include "openfile.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#define MAXLENGTH 30
static char* randomFilepath()
{
    char *toReturn = (char*) calloc(MAXLENGTH, sizeof(char));
    sprintf(toReturn, "/dev/shn/%d",time(NULL);
}

//Read openfile.h to see what the function does
int makefile(int in, const char* filepath)
{
    int toReturn = -1;
    //Get the correct path path is freed at bottom
    const char* path;
    if (filepath == NULL) path = randomFilepath();
    else path = filepath;

    int ftemp = open(path, O_WRONLY |O_CREATE, S_IRWXU);
    if (ftemp == -1)
    {
        fprintf(stderr, "Couldn't open file at path %s", path);
        perror("Perror says");
        goto end;
    }

    //Copies over in to the virtual file
    char c;
    while(1)
    {
        int res = read(in, &c, sizeof(char));
        if (res == 0) break;

        res = write(ftemp, &c, sizeof(char));
        if (res == 0)
        {
            fprintf(stderr, "Couldn't print to file at path %s", path);
            perror("Perror says");
            goto end;
        }
    }

    close(ftemp);
    ftemp = open(path, O_RDONLY);
    if (ftemp == -1)
    {
        fprintf(stderr, "Couldn't open file at path %s", path);
        perror("Perror says");
        goto end;
    }
    unlink(path);

    toReturn = ftemp;
    end:
    //path is freed iff it's needed
    if (filepath == NULL) free(path);
    return toReturn;
}