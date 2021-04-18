#ifndef HIDEFILE_H
#define HIDEFILE_H
#include <stdio.h>

//Takes the file that's supposed to be hidden, compresses it and append it to target.
//Target must hace writepermission and tohide must have read permission
int hidefile(FILE* target, FILE* tohide);


#endif