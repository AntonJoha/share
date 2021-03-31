#include "huffman.h"
#include <bzlib.h>
#include <string.h>
#define COMPRESS 1
#define DECOMPRESS 0

static bz_stream* initbz(int type)
{
    bz_stream *toReturn = malloc(sizeof(bz_stream));

    toReturn->bzalloc = NULL;
    toReturn->bzfree = NULL;
    toReturn->opaque = NULL;
    int ret;
    if (type == COMPRESS) ret = BZ2_bzCompressInit(toReturn, 9, DEBUG, WORKFACTOR);
    else ret = BZ2_bzDecompressInit(toReturn, DEBUG, 1);
    switch (ret)
    {
        case BZ_CONFIG_ERROR:
        fprintf(stderr, "BZ_CONFIG_ERROR\n");
        break;
        case BZ_PARAM_ERROR:
        fprintf(stderr, "BZ_PARAM_ERROR\n");
        break;
        case BZ_MEM_ERROR:
        fprintf(stderr, "BZ_MEM_ERROR");
        break;
        default:
        return toReturn;
    }
    fprintf(stderr, "Exiting...\n");
    exit(EXIT_FAILURE);
}
void huffmanencode(int in, int ou)
{
    char *test = "iwdgawdawddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddiudgiawd";
    char out[500] ={0};
    bz_stream *bz = initbz(COMPRESS);
    bz->next_in = test;
    bz->avail_in = strlen(test);
    bz->next_out = out;
    bz->avail_out = 500;
    BZ2_bzCompress(bz, BZ_RUN);
    BZ2_bzCompress(bz, BZ_FLUSH);
    printf("IN hejhejhejhej OUT %d, %d %c", bz->total_in_lo32, bz->total_in_hi32, out[0]);

    printf("\n START %d\n", bz->total_out_lo32);
    for (int i = 0; i < bz->total_out_lo32; ++i)
    {
        printf("%c", out[i]);
    }
    printf("\nEND\n");
    int len = bz->total_out_lo32;
    BZ2_bzCompressEnd(bz);
    bz = initbz(DECOMPRESS);
    char *newout = malloc(sizeof(char)*len +1);
    for(int i = 0; i < len; ++i) newout[i] = out[i];
    newout[len] = 0;
    bz->next_in =  newout;
    bz->avail_in = strlen(test);
    char buf[500];
    bz->next_out = buf;
    bz->avail_out = 500;
    BZ2_bzDecompress(bz);
    BZ2_bzDecompress(bz);
    printf("%d\n", bz->total_in_lo32);
    printf("%d\n", bz->total_out_lo32);
}

int main()
{
    huffmanencode(0,1);
}