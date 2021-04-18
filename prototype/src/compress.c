#include "compression.h"

#define ERRORCHECK(x, y, z) switch(x)\
                            {         \
                                case BZ_CONFIG_ERROR:   \
                                fprintf(stderr, "BZ_CONFIG_ERROR %s", y);   \
                                BZ2_bzWriteClose(NULL, z, 0, NULL, NULL); \
                                return x;   \
                                break;  \
                                case BZ_PARAM_ERROR:    \
                                fprintf(stderr, "BZ_PARAM_ERROR %s", y);    \
                                BZ2_bzWriteClose(NULL, z, 0, NULL, NULL); \
                                return x;   \
                                break;  \
                                case BZ_IO_ERROR:   \
                                fprintf(stderr, "BZ_IO_ERROR %s", y);   \
                                BZ2_bzWriteClose(NULL, z, 0, NULL, NULL); \
                                return x;   \
                                break;  \
                                case BZ_MEM_ERROR:  \
                                fprintf(stderr, "BZ_MEM_ERROR %s", y); \
                                BZ2_bzWriteClose(NULL, z, 0, NULL, NULL); \
                                return x;   \
                                break;  \
                                case BZ_SEQUENCE_ERROR: \
                                fprintf(stderr, "BZ_SEQUENCE_ERROR %s", y); \
                                BZ2_bzWriteClose(NULL, z, 0, NULL, NULL); \
                                return x;   \
                                break;  \
                                default:    \
                                break;  \
                            }

int compress_conf(FILE* in, FILE * out, int blocksize, int verbosity, int workFactor)
{
    
    int ret;
    BZFILE* b = BZ2_bzWriteOpen(&ret, out, blocksize, verbosity,workFactor);
    ERRORCHECK(ret, "BZ2_bzWriteOpen", b);

    int nBuf =  blocksize*100000;
    unsigned char *buf = (char*) malloc(sizeof(char*)*nBuf);
    int pos = 0;
    int c;
    while((c = fgetc(in)) != EOF)
    {
        buf[pos] = (unsigned char) c;
        ++pos;
        if (pos == nBuf)
        {
            BZ2_bzWrite(&ret, b, buf, pos);
            ERRORCHECK(ret, "BZ2_bzWrite", b);
            pos = 0;
        }
    }
    BZ2_bzWrite(&ret, b, buf, pos);
    ERRORCHECK(ret, "BZ2_bzWrite", b);

    BZ2_bzWriteClose(&ret, b, 0, NULL, NULL);
    if (ret =! BZ_OK && ret != BZ_RUN_OK)
    {
        ERRORCHECK(ret, "ERROR closing", b);
        return 0;
    }
    return 0;
}
