#include "huffman.h"
#include <fcntl.h>
int main()
{
    int in = open("trash", O_RDONLY);
    huffmanencode(in, 0);
}