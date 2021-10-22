#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "p3h.h"

void traverseInOrder(Node root, int code);

int codes[256];


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
    fread(buffer, fileSize, 1, filePtr);
    fclose(filePtr);
    unsigned int frequencies[256] = {0}; //hash map
    unsigned int i, j; //bytes read
    for(i = 0; i < fileSize; i++)
    { // reads file byte to byte
        frequencies[buffer[i]]++; //build hash map
    }
    // reduce hash map
    unsigned int elements[256][2] = {{0}, {0}}, elementsSize;
    for (i = 0, j = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            elements[j][0] = i;
            elements[j][1] = frequencies[i];
            j++;
        }
    }
    elementsSize = j;
    Node tree = createTree(elements, elementsSize);
    memset(codes, -1, 256 * sizeof(unsigned int)); //initialize codes in -1
    traverseInOrder(tree, 0);
    long long outputBits = 0;
    for(j = 0; j < 256; j++)
    {
        if(codes[j] != -1)
        {
            outputBits += getBitsCount(codes[j]) * frequencies[j];
        }
    }
    char* codedFilePath = malloc(sizeof(argv[1]) + 9 * sizeof(char));
    strcpy(codedFilePath, remove_ext(argv[1], '.','\\'));
    strcat(codedFilePath, "Huff.dat");
    FILE *codedFile = fopen(codedFilePath, "wb");
    if(!codedFile)
    {
        fprintf(stderr, "Error: file open failed '%s'.\n", codedFilePath);
        exit(1);
    }
    long outputBytes = (int)ceil((double)outputBits/8.0);
    unsigned char *output = calloc(outputBytes, sizeof(unsigned char));
    memset(output, 0, outputBytes * sizeof(unsigned char));
    int offset = 7;
    unsigned int k = 0;
    for(i = 0; i < fileSize; i++) // reads file byte to byte
        for(j = 0; j < 256; j++)
            if(buffer[i] == j) 
                writeByte(output, codes[j], &offset, &k);    
    fwrite(output, sizeof(output[0]), outputBytes, codedFile);
    fclose(codedFile);
    free(output);
    free(buffer);
    return 0;
}

/**
 *  traverse inorder binary tree to store leaf codes. 
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
        {
            codes[root->key] = code;
        }
        traverseInOrder(root->right, aux + 1);
    }
}
