#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "huffman_tree.h"
#include "huffman_code.h"

void traverseInOrder(Node root, int code);

int codes[256]; // stores Huffman codes for each byte

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: correct usage: ./%s filePath", argv[0]);
        return 1;
    }
    FILE *filePtr = fopen(argv[1], "rb"); //open file in binary read
    if (!filePtr)
    {
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    fseek(filePtr, 0, SEEK_END); // go to eof
    unsigned int fileSize = ftell(filePtr); // get the file size in bytes
    rewind(filePtr); // sets position of filePtr at the beginning
    unsigned char *buffer = calloc(fileSize, sizeof(unsigned char));
    if (!buffer)
    {
        perror("Error: buffer memory allocation failed");
        return 1;
    }
    fread(buffer, fileSize, 1, filePtr); // stores entire file in buffer
    fclose(filePtr);
    unsigned int frequencies[256] = {0}; //hash map
    unsigned int i, j; //bytes read
    for(i = 0; i < fileSize; i++)
    { // reads file byte to byte
        frequencies[buffer[i]]++; //build hash map
    }
    // reduce hash map and write it in auxFile
    FILE *auxFile = fopen("HuffAux.txt", "w");
    printf("\nFrequency table\n");
    unsigned int elements[256][2] = {{0}, {0}}, elementsSize;
    for (i = 0, j = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            elements[j][0] = i;
            elements[j][1] = frequencies[i];
            j++;
            printf("Byte: 0x%02x\tFreq: %d\n", i, frequencies[i]);
            fprintf(auxFile, "%d\n", i); // writes byte and frequency table
            fprintf(auxFile, "%d\n", frequencies[i]); // in auxFile
        }
    }
    elementsSize = j;
    printf("\nHuffman Tree\n");
    Node tree = createTree(elements, elementsSize); // Huffman tree for codes
    memset(codes, -1, 256 * sizeof(unsigned int)); //initialize codes in -1
    traverseInOrder(tree, 0); // store byte codes into codes array
    unsigned long long outputBits = 0;
    for(j = 0; j < 256; j++)
        if(codes[j] != -1) // bits count to write in coded file
            outputBits += getBitsCount(codes[j]) * frequencies[j];
    fprintf(auxFile, "%llu\n", outputBits); // writes outputBits in auxFile
    char* codedFilePath = calloc(255, sizeof(char));
    if (!codedFilePath)
    {
        perror("Error: codedFilePath memory allocation failed");
        return 1;
    }
    char* extension = calloc(255-strlen(argv[1]), sizeof(char));
    if (!extension)
    {
        perror("Error: extension memory allocation failed");
        return 1;
    }
    strcpy(codedFilePath, argv[1]);
    stripExtension(codedFilePath, extension);
    strcat(codedFilePath, "Huff.dat");
    printf("Encoded filename: %s, og extension: %s\n", codedFilePath, extension);
    FILE *codedFile = fopen(codedFilePath, "wb"); // created file to store encoded
    if(!codedFile)
    {
        fprintf(stderr, "Error: file open failed '%s'.\n", codedFilePath);
        exit(1);
    }
    unsigned long outputBytes = (int)ceil((double)outputBits/8.0); // bytes count to write
    fprintf(auxFile, "%lu\n", fileSize); // writes fileSize in auxFile
    fprintf(auxFile, "%s", extension); // writes extension in auxFile
    fclose(auxFile);
    unsigned char *output = calloc(outputBytes, sizeof(unsigned char));
    memset(output, 0, outputBytes * sizeof(unsigned char)); // initialize output in 0
    int offset = 7; // most significant bit offset
    unsigned int k = 0; // index for output
    for(i = 0; i < fileSize; i++) // visits every byte in buffer
        for(j = 0; j < 256; j++)
            if(buffer[i] == j) // wirte codes in output
                writeByte(output, codes[j], &offset, &k);    
    fwrite(output, sizeof(output[0]), outputBytes, codedFile);
    fclose(codedFile);
    free(output);
    free(buffer);
    return 0;
}

/**
 *  traverse inorder Huffman tree to store leaf codes. 
 *  @param root binary tree root node.
 *  @param code leaf node code
*/
void traverseInOrder(Node root, int code)
{
    if (root != NULL)
    {
        int aux = 2*code;
        traverseInOrder(root->left, aux);
        if(root->key != NOITEM)
            codes[root->key] = code;
        traverseInOrder(root->right, aux + 1);
    }
}
