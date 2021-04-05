#include <stdio.h>
#include "globalnames.h" 


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
        fseek(f, SEEK_END - pos);
        int res = getc(f);
        if (res == 0 || res == EOF) break;
        res -= '0';
        for (int i = 1; i < pos; ++i) res*=10;
        toReturn += res;
    }

    fseek(f, before);

    //Important to add the final informationbytes aswell
    toReturn += pos;
    return toReturn;
}

//Is given a ELF file with data hidden at the end.
//Returns a filepointer to the start of the embedded file section.
FILE * getembeddedfile(FILE * f, long pos)
{

    FILE * toReturn = f;
    
    fseek(f, SEEK_END - pos);
    return f;

}

//Is given a ELF file with data hidden at the end. 
//The path should be a path to some folder, remember that this is where the file is going to be temporarly stored.
//If in doubt call decompresseembeddedfile instead
//The given file is opened with executionpermissions and is unlinked.
//This is because the only point of it is to more or less just be executed and discarded.
int decompressembeddedfile_path(FILE * f,const char *p)
{
    int length = strlen(p);
    char* path = (char*) malloc(sizeof(char)*length);
    strcpy(path, p);
    long pos = getembeddedfilesize(f);
    
    unsigned int r = (unsigned int) &pos;
    for (int i = length - 1; i > 0; i--)
    {
        if (path[i] != 'X') break;
        else path[i] -= (r % (i % 10));
    }
    close(open(path, O_CREAT | O_RDONLY, S_IRWXU));

    FILE *in = getembeddedfile(f, pos);
    FILE* out = fopen(path, "w");
    int ret = decompress(in, out);

    


}

//Is given a ELF file with data hidden at the end.
//Returns a file with the decompressed data
//The given file is opened with executionpermissions and is unlinked.
//This is because the only point of it is to more or less just be executed and discarded.
int decompressembeddedfile(FILE * f)
{
    return decompressembeddedfile_path(f, STANDARDPATH);
}