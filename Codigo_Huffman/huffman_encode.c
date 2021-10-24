#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "huffman_tree.h"
#include "huffman_code.h"

void getCodes(Node root, int code, int length);

int codes[256][2]; // stores Huffman codes and its length

int main(int argc, char *argv[])
{
    if (argc != 2)
    { // usage error
        fprintf(stderr, "Usage: ./%s <file path>\n", argv[0]);
        return 1;
    }
    FILE *filePtr = fopen(argv[1], "rb"); //open file in binary read
    if (!filePtr)
    { // file open error
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    fseek(filePtr, 0, SEEK_END); // go to eof
    unsigned int fileSize = ftell(filePtr); // get the file size in bytes
    rewind(filePtr); // sets position of filePtr at the beginning
    unsigned char *buffer = calloc(fileSize, sizeof(unsigned char));
    if (!buffer)
    {  // memory allocation error
        perror("Error: buffer memory allocation failed\n");
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
    char *filePath = calloc(strlen(argv[1]) + 11, sizeof(char));
    char* extension = calloc(255-strlen(argv[1]), sizeof(char));
    if (!filePath || !extension)
    { // error allocating memory
        perror("Error: aux file path or extension memory allocation failed.\n");
        return 1;
    }
    strcpy(filePath, argv[1]); // copy og file path
    stripExtension(filePath, extension);
    strcat(filePath, "HuffAux.txt");
    FILE *auxFile = fopen(filePath, "w"); // create aux file
    if (!auxFile)
    { // file creation error
        perror("Error: file creation failed 'HuffAux.txt'.\n");
        return 1;
    }
    unsigned int elements[256][2] = {{0}, {0}}, elementsSize;
    for (i = 0, j = 0; i < 256; i++)
        if (frequencies[i] != 0)
        { // reduce hash map and write it in aux file
            elements[j][0] = i;
            elements[j][1] = frequencies[i];
            j++;
            fprintf(auxFile, "%u\n", i); // writes byte and frequency table
            fprintf(auxFile, "%u\n", frequencies[i]); // in aux file
        }
    elementsSize = j;
    fprintf(auxFile, "%u\n", NOITEM); // writes NOITEM in axu file
    fprintf(auxFile, "%u\n", fileSize); // writes fileSize in aux file
    fprintf(auxFile, "%s", extension); // writes extension in aux file
    fclose(auxFile);
    printf("\nHuffman coding aux file: %s\n", filePath);
    Node root = buildTree(elements, elementsSize); // Huffman tree for codes
    memset(codes, -1, 512 * sizeof(unsigned int)); //initialize codes in -1
    getCodes(root, 0, 0);// store byte codes into codes array
    unsigned long long outputBits = 0;
    for(j = 0; j < 256; j++)
        if(codes[j][0] != -1) // bits count to write in coded file
            outputBits += codes[j][1] * frequencies[j];
    strcpy(filePath, argv[1]); // copy og file path
    stripExtension(filePath, extension);
    free(extension); // extension no longer needed
    strcat(filePath, "Huff.dat");
    FILE *codedFile = fopen(filePath, "wb"); // created file to store encoded
    if(!codedFile)
    { // file creation error
        fprintf(stderr, "Error: file creation failed '%s'.\n", filePath);
        exit(1);
    } // bytes to write in coded file
    unsigned long outputBytes = (int)ceil((double)outputBits/8.0);
    unsigned char *output = calloc(outputBytes, sizeof(unsigned char));
    if (!output)
    { // memory allocation error
        perror("Error: output memory allocation failed.\n");
        return 1;
    }
    memset(output, 0, outputBytes * sizeof(unsigned char)); // init output in 0
    short offset = 7; // offset for the first byte
    unsigned int k = 0; // index for output
    for(i = 0; i < fileSize; i++) // visits every byte in buffer
        for(j = 0; j < 256; j++)
            if(buffer[i] == j) // write codes in output
                writeCode(output, codes[j], &offset, &k);
    fwrite(output, sizeof(output[0]), outputBytes, codedFile);
    fclose(codedFile); // write coded file n close it
    printf("Huffman encoded file: %s\n", filePath);
    free(filePath);
    freeTree(root);
    root = NULL;
    free(output);
    free(buffer);
    return 0;
}

/**
 *  preorder traverse Huffman tree to store leaf codes. 
 *  @param root binary tree root node.
 *  @param code used to store the current code.
*/
void getCodes(Node root, int code, int length)
{
    if (root->byte != NOITEM)
    { // leaf node
        codes[root->byte][0] = code;
        codes[root->byte][1] = length;
    }
    else
    { // internal node
        getCodes(root->left, code << 1, length + 1);
        getCodes(root->right, (code << 1) + 1, length + 1);
    }
}
