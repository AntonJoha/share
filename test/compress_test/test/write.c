#include "test.h"

FILE*   f;
BZFILE* b;
int     nBuf;
char    buf[5000 ];
int     bzerror;
int     nWritten;
int main(){
f = fopen ( TEMP, "wb" );
if ( !f ) {
 /* handle error */
}
FILE *in = fopen(IN, "rb");
char c;
int pos = 0;
while(fscanf(in,"%c", &c) != EOF)
{
  buf[pos] = c;
  ++pos;
}

b = BZ2_bzWriteOpen( &bzerror, f, 9, 4, 30 );
if (bzerror != BZ_OK) {
 BZ2_bzWriteClose ( &bzerror ,b, 0, NULL, NULL );
 fprintf(stderr, "ERROR");
 exit(EXIT_FAILURE);
}
nBuf = 769;
nWritten = 0;
while ( pos - nWritten > 0) {
 /* get data to write into buf, and set nBuf appropriately */
 pos -= nWritten;
 BZ2_bzWrite ( &bzerror, b, buf, nBuf );
 nWritten = nBuf;
 if (bzerror == BZ_IO_ERROR) { 
   BZ2_bzWriteClose ( &bzerror, b , 0,NULL, NULL);
 }
}

BZ2_bzWriteClose( &bzerror, b , 0, NULL, NULL);
if (bzerror == BZ_IO_ERROR) {
 /* handle error */
}
fclose(in);
fclose(f);
}