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
    close(open(tempname, O_WRONLY |O_CREAT, S_IRWXU));

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
    if (ret != 0)
    {
        fprintf(stderr, "Error in decompress\n");
        return -1;
    }
    fclose(in);
    fclose(out);

    int f = open(tempname, O_RDONLY,  S_IRWXU);
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
       
        res = fexecve(file, argv, envp);
        fprintf(stderr, "This shouldn't print\n");
        perror("Perror says");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    close(file);
    return;
}
