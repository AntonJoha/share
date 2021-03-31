#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 2
#define WORKFACTOR 30

struct hufftree{
    int leaf;
    struct hufftree* left;
    struct hufftree* right;
    unsigned char value;
    int weight;
};

typedef struct node{
    char *encoding;
    size_t length;
}huffnode;

typedef struct huffhash{
    huffnode list[256];
} huffhash;


typedef struct hufftree* treeprt;


//Takes a file encoded with huffmans encoding
//Returns a filepointer to the decoded version
int huffmandecode(int in);

//Takes a file
//outputs the decoded version to out
void huffmanencode(int in, int out);

#endif