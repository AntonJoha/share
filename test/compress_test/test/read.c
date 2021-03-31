#include "test.h"

FILE*   f;
BZFILE* b;
int     nBuf;
char    buf[ 5000 ];
int     bzerror;
int     nWritten;

int main(){
f = fopen (TEMP , "r" );
if ( !f ) {
  fprintf(stderr, "ERROR");
  exit(EXIT_FAILURE);
}
b = BZ2_bzReadOpen ( &bzerror, f, 0, 0,NULL, 0 );
if ( bzerror != BZ_OK ) {
  BZ2_bzReadClose ( &bzerror, b );
  fprintf(stderr, "ERROR");
  exit(EXIT_FAILURE);
}

FILE* out = fopen(OUT, "w");
bzerror = BZ_OK;
while ( bzerror == BZ_OK) {
  nBuf = BZ2_bzRead ( &bzerror, b, buf, 5000 );
  if ( bzerror == BZ_OK ) {
    for (int i = 0;  i < nBuf; ++i)
    {
      fprintf(out, "%c", buf[i]);
    }
  }
}

fclose(f);

for (int i = 0; i < nBuf; ++i)
{
  fprintf(stdout, "%c", buf[i]);
  fprintf(out, "%c", buf[i]);
}

fclose(out);
if ( bzerror != BZ_STREAM_END ) {
   BZ2_bzReadClose ( &bzerror, b );
} else {
   BZ2_bzReadClose ( &bzerror, b );
}
}