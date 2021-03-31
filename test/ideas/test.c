#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define _GNU_SOURCE


int main(int argc, char *argv[], char * envp[])
{

	int file = open("a.out", O_RDONLY);
	if (file == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	char tempname[] = "/dev/shm/t";
	int ftemp = open(tempname, O_WRONLY | O_CREAT, S_IRWXU);
	if (ftemp == -1)
	{
		perror("Error opening temp file");
		exit(EXIT_FAILURE);
	}
	char c;
	printf("ahwd\n");
	while(1)
	{
		int res = read(file, &c, 1);
		printf("%d %c\n",res, c);
		if (res == 0) break;

		res = write(ftemp, &c, sizeof(char ));
		if (res < 1)
		{
			perror("INTE BRA :( \n");
			break;
		}

	}
	printf("wha\n");
	fflush(stdin);
	close(ftemp);
	ftemp  = open(tempname, O_RDONLY);
	unlink(tempname);
	int res = fork();
	if (res == -1)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
	}

	if(!res)
	{	
		res = fexecve(ftemp, argv, envp);
		printf("This shouldn't print \n %d", res);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	close(file);

}
