#include "compression.h"
#define IN "info/in"
#define OUT "info/out"
#define TEMP "info/temp"

int main()
{
    FILE* in = fopen(IN, "rb");
    FILE* out = fopen(TEMP, "wb");
    //compress(in,out);
    fclose(in);
    fclose(out);
    in = fopen("print.c", "rb");
    out = fopen(OUT, "wb");
    decompress(in,out);
    fclose(in);
    fclose(out);
}
