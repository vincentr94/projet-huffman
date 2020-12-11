/**
 * @file main.c
 * @brief Fichier main
 * @author Faël MOULOUDJ
 * @version 1.0
 * @date 4/12/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


int main()
{
    FILE* input = fopen("input.txt","r");
    Compression(input);
    fclose(input);
    return 0;
}

