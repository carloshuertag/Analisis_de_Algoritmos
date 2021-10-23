#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "huffman_tree.h"
#include "huffman_code.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    { // usage error
        fprintf(stderr, "Usage: ./%s <filePath> <auxFilePath>", argv[0]);
        return 1;
    }
    FILE *auxFilePtr = fopen(argv[2], "r"); // open aux file
    if (!auxFilePtr)
    { // error opening file
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[2]);
        return 1;
    }
    unsigned int elements[256][2] = {{0}, {0}}, elementsSize = 0;
    unsigned long long bitsCount;
    unsigned long ogFileSize;
    char *extension = calloc(264 - strlen(argv[1]), sizeof(char));
    if (!extension)
    { // error allocating memory
        fprintf(stderr, "Error: extension memory allocation failed.\n");
        return 1;
    }
    while (auxFilePtr && !feof(auxFilePtr))
    { // read file until EOF
        fscanf(auxFilePtr, "%u", &elements[elementsSize][0]);
        if (elements[elementsSize][0] == NOITEM)
        {
            fscanf(auxFilePtr, "%llu", &bitsCount);
            fscanf(auxFilePtr, "%lu", &ogFileSize);
            fscanf(auxFilePtr, "%s", extension);
            break;
        }
        else
        {
            fscanf(auxFilePtr, "%u", &elements[elementsSize][1]);
            elementsSize++;
        }
    }
    fclose(auxFilePtr);
    int i;
    printf("\nFrequency Table\n");
    for (i = 0; i < elementsSize; i++)
    { // print elements
        printf("Byte: 0x%02x\tFreq: %d\n", elements[i][0], elements[i][1]);
    }
    printf("\nExtension: %s\n", extension);
    printf("Bits count: %llu\n", bitsCount);
    printf("Original file size: %lu\n", ogFileSize);
    printf("\nHuffman Tree\n");
    Node tree = buildTree(elements, elementsSize); // Huffman tree for codes
    char *filePath = calloc(strlen(argv[1]) + strlen(extension), sizeof(char));
    if (!filePath)
    { // error allocating memory
        fprintf(stderr, "Error: file path memory allocation failed.\n");
        return 1;
    }
    strcpy(filePath, argv[1]); // copy og file path
    stripExtension(filePath, argv[2]); // argv[2] won't be necessary
    strcat(filePath, extension); // add og extension
    printf("\nFile path: %s\n", filePath);
}