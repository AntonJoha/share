#include "compression.h"

#define BUFSIZE 100000000

#define ERRORCHECK(x,y,z)    switch(x) \
                            {         \
                                case BZ_CONFIG_ERROR:   \
                                fprintf(stderr, "BZ_CONFIG_ERROR %s", y);   \
                                BZ2_bzReadClose(NULL, z); \
                                return x;   \
                                break;  \
                                case BZ_PARAM_ERROR:    \
                                fprintf(stderr, "BZ_PARAM_ERROR %s", y);    \
                                BZ2_bzReadClose(NULL, z); \
                                return x;   \
                                break;  \
                                case BZ_IO_ERROR:   \
                                fprintf(stderr, "BZ_IO_ERROR %s", y);   \
                                BZ2_bzReadClose(NULL, z); \
                                return x;   \
                                break;  \
                                case BZ_MEM_ERROR:  \
                                fprintf(stderr, "BZ_MEM_ERROR %s", y); \
                                BZ2_bzReadClose(NULL, z); \
                                return x;   \
                                break;  \
                                case BZ_SEQUENCE_ERROR: \
                                fprintf(stderr, "BZ_SEQUENCE_ERROR %s", y); \
                                BZ2_bzReadClose(NULL, z); \
                                return x;   \
                                break;  \
                                case BZ_DATA_ERROR_MAGIC: \
                                fprintf(stderr, "BZ_DATA_ERROR_MAGIC %s", y);   \
                                BZ2_bzReadClose(NULL, z);   \
                                return x;   \
                                break;  \
                                case BZ_STREAM_END: \
                                fprintf(stderr, "BZ_STREAM_END %s", y); \
                                BZ2_bzReadClose(NULL, z);   \
                                return x;   \
                                break;  \
                                case BZ_UNEXPECTED_EOF: \
                                fprintf(stderr, "BZ_UNEXPECTED_EOF %s", y); \
                                BZ2_bzReadClose(NULL, z);   \
                                return x;   \
                                break;  \
                                default:    \
                                break;  \
                            }

int decompress_conf(FILE* in, FILE* out, int verbosity, int small, void* unused, int nUnused)
{
    int ret;
    BZFILE* b = BZ2_bzReadOpen(&ret, in, verbosity, small, unused, nUnused);
    ERRORCHECK(ret, "READOPEN",b);

    unsigned char *buf = (unsigned char*) malloc(sizeof(unsigned char)* BUFSIZE );

    while(ret != BZ_STREAM_END)
    {
        int read = BZ2_bzRead(&ret, b, buf, BUFSIZE);
        printf("Firstread ye\n");
        if (ret != BZ_OK && ret != BZ_STREAM_END)
        {
            ERRORCHECK(ret, "READ ", b);
        }
        for (int i = 0; i < read; ++i)
        {
            fprintf(out, "%c", buf[i]);
        }
    }
    BZ2_bzReadClose(&ret, b);
    ERRORCHECK(ret, "READCLOSE", b);
    return 0;
    
}

