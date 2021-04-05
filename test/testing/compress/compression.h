#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <bzlib.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCKSIZE 9
#define VERBOSITY 0
#define WORKFACTOR 0

//Same as compress but the specific values can be set.
//Check the manual for libbzip2 before using this to know what is all does
int compress_conf(FILE* in, FILE * out, int blocksize, int verbosity, int workFactor);

//Take the filepointer in and compress the data it points to.
//It must have read access.
//The result is printed to out, out must have write access.
//Both files must be open as binary files, if not then unknown errors might occur.
static inline int compress(FILE* in, FILE* out)
{
   return compress_conf(in, out, BLOCKSIZE, VERBOSITY, WORKFACTOR); 
}
//same as decompress but the specific values can be set.
//Check the manual for libbzip2 before using this to know what it all does. 
int decompress_conf(FILE* in, FILE* out, int verbosity, int small, void* unused, int nUnused);
//Take the filepointer in and decompress the data it points to.
//It must have read access.
//The result is printed to out, out must have write access.
//Both files must be open as binary files, if not the unknown errors might occur. 
static inline int decompress(FILE* in, FILE* out)
{
    return decompress_conf(in , out, VERBOSITY, 0, NULL, 0);
}


#endif