#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>

int main()
{
    FILE* input = fopen("input.txt","r");
    Compression(input);
    fclose(input);
    return 0;
}

