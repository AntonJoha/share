#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "globalnames.h" 
#include "hiddenfile.h"
#include "compression.h"

//Is given a ELF file with data hidden at the end. 
//The last bytes is used to know the size of the file and should be used in combination with fseek to find the right position
//The file returns to the same position as it was before
unsigned long getembeddedfilesize(FILE* f)
{
    long pos = 1;
    long before = ftell(f);
    unsigned long toReturn = 0;

    while(1)
    {
        fseek(f, -pos, SEEK_END);
        int res = getc(f);
        if (res == 0 || res == EOF) break;
        res -= '0';
        for (int i = 1; i < pos; ++i) res*=10;
        toReturn += res*sizeof(char);
        ++pos;
    }

    fseek(f, before, SEEK_SET);

    //Important to add the final informationbytes aswell
    toReturn += pos -1;
    return toReturn;
}

//Is given a ELF file with data hidden at the end.
//Returns a filepointer to the start of the embedded file section.
FILE * getembeddedfile(FILE * f, long pos)
{

    FILE * toReturn = f;
    
    fseek(toReturn, -pos,SEEK_END);
  
    return toReturn;

}

//Is given a ELF file with data hidden at the end. 
//The path should be a path to some folder, remember that this is where the file is going to be temporarly stored.
//If in doubt call decompresseembeddedfile instead
//The given file is opened with executionpermissions and is unlinked.
//This is because the only point of it is to more or less just be executed and discarded.
int decompressembeddedfile_path(FILE * f,const char *p)
{
    int length = strlen(p);
    long pos = getembeddedfilesize(f);
    
    #define path "out" //THIS IS EXTREMLY TEMPORARY AND ONLY USED FOR A TEST
    #ifndef path
    char* path = (char*) malloc(sizeof(char)*length);
    strcpy(path, p);
    */
   
    
    //Psuedorandom generation of a name. 
    unsigned int r = (unsigned int) &pos;
    for (int i = length - 1; i > 0; i--)
    {
        if (path[i] != 'X') break;
        else path[i] -= (r % (i % 10));
    }
    #endif
 
    //Creates and close the file immediatly. This is done to make sure that the right priviliges are set
    //Only because fopen is used deeper down
    //LONG TERM: GET RID OF FOPEN SO THIS ISN't NEEDED
    close(open(path, O_CREAT | O_RDONLY, S_IRWXU));

    FILE* in = getembeddedfile(f, pos);
    FILE* out = fopen(path, "w");

    if (decompress(in, out) != 0)
    {
        fprintf(stderr, "Error decompressing hidden file\n exiting...\n");
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }
    fclose(in);
    fclose(out);

    int toReturn = open(path, O_RDONLY);
    //unlink(path);
    return toReturn;
}

//Is given a ELF file with data hidden at the end.
//Returns a file with the decompressed data
//The given file is opened with executionpermissions and is unlinked.
//This is because the only point of it is to more or less just be executed and discarded.
int decompressembeddedfile(FILE * f)
{
    return decompressembeddedfile_path(f, DEFAULTPATH);
}





