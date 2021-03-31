#include <sys/mount.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

//trying to use local tmpfs
int main(int argc, char *argv[])
{
    char *test = calloc(30, sizeof(char));
    sprintf(test, "/dev/shn/%d",time(NULL));
    printf("%s", test);
}