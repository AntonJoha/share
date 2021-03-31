#ifndef GETFILE_H
#define GETFILE_H

//Give a path to a compressed file.
//Return a file handle to a file with the decompressed information
//The file is returned with the flag O_RDONLY and is unlinked so it's gone after the program ends
//Returns -1 if something goes wrong
int getfiledecompressed(char* path);

void executecompressed(char* path, char * argc[], char* envp[]);

#endif