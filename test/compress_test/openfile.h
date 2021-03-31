#ifndef OPENFILE_H
#define OPENFILE_H

//Takes a filepointer to be copied into a temporary path
//The given file is then unlisted, thus making sure that it's "gone"
//Returns the file to be executed by fexecve
//If an error occur return -1 and print info to stderr
//
//the file given must have read permissions to it.
//If no filepath is given then /dev/shn/ is used with a random name
//The filepath should be on a virtual drive.
//This is only neccesary if the given file has both read and write permissions
int makefile(int in, const char* filepath);

#endif