#include <bzlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define IN "info/in"
#define TEMP "info/temp"
#define OUT "info/out"



int main()
{
    FILE* in = fopen(IN, "rb");
    FILE* f = fopen(TEMP, "wr");
    int res;
    BZFILE * bzfile = BZ2_bzWriteOpen(&res, f, 9, 2, 0);
    if (res != BZ_OK)
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }
    char buf[5000];
    char c;
    int pos = 0;
    while(fscanf(in,"%c", &c) != EOF)
    {
        buf[pos] = c;
        ++pos;
    }
    int len = 769;
    BZ2_bzWrite(&res, bzfile,&buf, len);

    if (res != BZ_OK)
    {
        fprintf(stderr, "Error write");
        exit(EXIT_FAILURE);
    }

    BZ2_bzWriteClose(&res, bzfile, 0, NULL, NULL);
    fclose(in);
    fclose(f);
    in = fopen(TEMP, "rb");
    bzfile = BZ2_bzReadOpen(&res,in, 4 ,0, NULL,0);
    if (res != BZ_OK)
    {
        fprintf(stderr, "Error Read open");
        exit(EXIT_FAILURE);
    }

    FILE * out = fopen(OUT, "w");
    int r;
    char b[5000];
    while(res == BZ_OK)
    {
        r = BZ2_bzRead(&res, bzfile, b, 5000);
        printf("AMOUNT READ %d", r);
    }
    fclose(in);

    printf("\n\n");
    for (int i= 0; i < r; ++i)
    {
        fprintf(stdout, "%c", b[i]);
        fprintf(out, "%c", b[i]);
    }
    fclose(out);
    printf("\n\n");
}