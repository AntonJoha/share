#include "filehandling.h"
#include "compression.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#define TEMPLENGTH 25


//Check h-file for description
int getfiledecompressed(char* path)
{

    char tempname[TEMPLENGTH];
    int t = time(NULL);

    sprintf(tempname, "/dev/shm/%d", time);

    FILE* in = fopen(path, "r");
    if (!in)
    {
        fprintf(stderr, "Error opening file %s\n", path);
        perror("Perror says: ");
        return -1;
    }
    FILE* out = fopen(tempname, "w");
    if (!out)
    {
        fprintf(stderr, "Error opening file %s\n", tempname);
        perror("Perror says: ");
        return -1;
    }


    int ret = decompress(in, out);
    if (!ret)
    {
        fprintf(stderr, "Error in decompress\n");
        return -1;
    }
    fclose(in);
    fclose(out);

    int f = open(tempname, O_RDONLY);
    if (f == -1)
    {
        fprintf(stderr, "Error opening file %s\n", tempname);
        perror("Perror says: ");
        return -1;
    }
    unlink(tempname);
    return f;
}


void executecompressed(char* path, char *argv[], char* envp[])
{
    int file = getfiledecompressed(path);
    if (file == -1)
    {
        fprintf(stderr, "Error with getfiledecompressed with argument %s\n", path);
        exit(EXIT_FAILURE);
    }  

    int res = fork();

    if (res == -1)
    {
        fprintf(stderr, "Error with fork\n");
        exit(EXIT_FAILURE);
    }

    if (res)
    {
        if (argv == NULL)
        {
            argv[0] = "prog";
        }
        if (envp == NULL)
        {
            envp[0] = "user=NAMENOTUSEDIHOPE";
        }
        res = fexecve(file, argv, envp);
        fprintf(stderr, "This shouldn't print\n");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    close(file);
    return;
}
