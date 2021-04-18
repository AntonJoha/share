#include "hidefile.h"

int main(int argc, char*argv[])
{
    FILE * tohide = fopen(argv[1], "r");
    FILE * target = fopen(argv[2], "a");
    hidefile(target,tohide);
}