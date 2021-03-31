#include <stdio.h>



int main()
{
	int i = 600345;
	FILE* f = fopen("a.out", "r");
	while(1)
	{
		char c;
		if(fscanf(f, "%c", &c) == EOF) break;
		printf("%c",c);
	}

	fclose(f);
	printf("HejHej\n");
	printf("iwhdahjdwgidaw\n\n\n");
}
