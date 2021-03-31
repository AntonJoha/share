#include <stdio.h>

int main(int argc, char * argv[])
{
	FILE* f = fopen("a.c.out", "w");
	fprintf(f,"%s", argv[0]);
	fclose(f);
}
