#include "hidefile.h"
#define TESTOUT "target"
#define TOHIDE "tohide"


int main()
{
    FILE * tohide = fopen(TOHIDE, "r");
    FILE * target = fopen(TESTOUT, "a");
    hidefile(target,tohide);
}