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
        fprintf(stderr, "Usage: ./%s <file path> <aux file path>\n", argv[0]);
        return 1;
    }
    FILE *auxFilePtr = fopen(argv[2], "r"); // open aux file
    if (!auxFilePtr)
    { // error opening file
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[2]);
        return 1;
    }
    unsigned int elements[256][2] = {{0}, {0}},
                elementsSize = 0, fileSize;
    unsigned long long bitsCount;
    char *extension = calloc(264 - strlen(argv[1]), sizeof(char));
    if (!extension)
    { // error allocating memory
        perror("Error: extension memory allocation failed.\n");
        return 1;
    }
    while (auxFilePtr && !feof(auxFilePtr))
    { // read file until EOF
        fscanf(auxFilePtr, "%u", &elements[elementsSize][0]);
        if (elements[elementsSize][0] == NOITEM)
        {
            fscanf(auxFilePtr, "%llu", &bitsCount);
            fscanf(auxFilePtr, "%u", &fileSize);
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
    printf("\nFrequency Table\n");
    int p;
    for (p = 0; p < elementsSize; p++)
        printf("Byte: 0x%02x\tFreq: %d\n", elements[p][0], elements[p][1]);
    printf("\nExtension: %s\n", extension);
    printf("Bits count: %llu\n", bitsCount);
    printf("Original file size: %u\n", fileSize);
    printf("\nHuffman Tree\n");
    Node tree = buildTree(elements, elementsSize); // Huffman tree for codes
    printTree(tree);
    FILE* encodedFilePtr = fopen(argv[1], "rb"); // open encoded file])
    if (!encodedFilePtr)
    { // error opening file
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    fseek(encodedFilePtr, 0, SEEK_END); // go to eof
    unsigned int encodedFileSize = ftell(encodedFilePtr); // get the file bytes
    rewind(encodedFilePtr); // sets position of filePtr at the beginning
    unsigned char *buffer = calloc(encodedFileSize, sizeof(unsigned char));
    if (!buffer)
    { // error allocating memory
        perror("Error: buffer memory allocation failed.\n");
        return 1;
    } // initialize buffer in 0
    fread(buffer, sizeof(unsigned char), encodedFileSize, encodedFilePtr);
    fclose(encodedFilePtr); // read entire encoded file n close it
    char *filePath = calloc(strlen(argv[1]) + strlen(extension), sizeof(char));
    if (!filePath)
    { // error allocating memory
        perror("Error: file path memory allocation failed.\n");
        return 1;
    }
    strcpy(filePath, argv[1]); // copy og file path
    stripExtension(filePath, argv[2]); // argv[2] no longer needed, storing ".dat"
    strcat(filePath, extension); // add og extension
    free(extension); // extension no longer needed
    printf("\nFile path: %s\n", filePath);
    FILE *filePtr = fopen(filePath, "wb"); // create decoded file
    if (!filePtr)
    { // file creation error
        fprintf(stderr, "Error: file creation failed '%s'.\n", filePath);
        return 1;
    }
    unsigned char *output = calloc(fileSize, sizeof(unsigned char));
    if (!output)
    {  // memory allocation error
        perror("Error: output memory allocation failed\n");
        return 1;
    }
    unsigned long long i;
    unsigned int j, k;
    short codeLength = 0, codeLenAcc = 0, offset = 7;
    Node node = tree; // start at root
    /*for(i = 0, j = 0, k = 0; i < bitsCount; i++)
    {
        if(offset < 0)
        {
            offset = 7;
            j++;
        }
        if(getBitAt(buffer[j], offset--) & 1)
            node = node->right;
        else
            node = node->left;
        if(node->byte != NOITEM)
        { // leaf node
            output[k++] = node->byte;
            node = tree; // reset node to root
            printf("\nOutput: 0x%02x", output[k - 1]);
        }
    }*/
    for(i = 0, j = 0, k = 0; i < bitsCount; i += codeLength)
    { // write bytes in output from codes at input
        writeBytes(node, buffer, output, &offset, &j, &k, &codeLenAcc);
        codeLength = codeLenAcc; // written byte's code length
        codeLenAcc = 0; // reset code length accumulator
        node = tree; // reset node to root
        printf("\nOutput: 0x%02x Code length: %hd", output[k - 1], codeLength);
    }
    printf("\nOutput length vs original file size comparisson: %u == %u: %d\n", fileSize, k, fileSize == k);
    fwrite(output, sizeof(output[0]), fileSize, filePtr); // write decoded file
    fclose(filePtr);
    free(filePath);
    free(tree);
    free(buffer);
    free(output);
    return 0;
}
