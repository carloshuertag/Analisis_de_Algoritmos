#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "p3h.h"

int compareTo(const void *a, const void *b);
void traverseInOrder(Node root, int code);

int codes[256];

void printDecToBin(int dec) {
    if(dec > 1){
        printDecToBin(dec>>1);
    }
    printf("%d", dec&1);
}

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
    unsigned char *buffer = malloc(sizeof(unsigned char));
    if (!buffer)
    {
        perror("Error: buffer memory allocation failed");
        return 1;
    }
    unsigned int frequencies[256] = {0}; //hash map
    size_t bytes = 0; //bytes read
    while ((bytes = fread(buffer, sizeof(*buffer), 1, filePtr)) == 1)
    { // reads file byte to byte
        frequencies[*buffer]++; //build hash map
    }
    // reduce hash map
    unsigned int elements[256][2] = {{0}, {0}}, elementsSize;
    int i, j;
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
    qsort(elements, elementsSize, 2 * sizeof(unsigned int), compareTo);
    for (j = 0; j < elementsSize; j++)
    {
        printf("\n0x%02x\t%d", elements[j][0], elements[j][1]);
    }
    Node tree = createTree(elements, elementsSize);
    memset(codes, -1, 256 * sizeof(int)); //initialize codes in -1
    traverseInOrder(tree, 0);
    for(j = 0; j < 256; j++)
    {
        if(codes[j] != -1)
        {
            printf("\n0x%02x: code: (0x%02x)", j, codes[j]);
            printDecToBin(codes[j]);
        }
    }
    rewind(filePtr); // Sets position of filePtr at the beginning
    char* codedFilePath = malloc(sizeof(argv[1]) + 9 * sizeof(char));
    strcpy(codedFilePath, remove_ext(argv[1], '.','\\'));
    strcat(codedFilePath, "Huff.dat");
    FILE *codedFile = fopen(codedFilePath, "wb");
    if(!codedFile)
    {
        fprintf(stderr, "Error: file open failed '%s'.\n", codedFilePath);
        exit(1);
    }
    printf("\n");
    i = 0;
    while ((bytes = fread(buffer, sizeof(*buffer), 1, filePtr)) == 1)
    { // reads file byte to byte
        for(j = 0; j < 256; j++)
        {
            if(*buffer == j)
            {
                //write in file codes[j[]]
                //fwrite(&sth, sizeof(sth), 1, codedFile)
            }
        }
        printf("0x%02x\t", *buffer);
        i++;
    }
    fclose(filePtr);
    free(buffer);
    return 0;
}

int compareTo(const void *a, const void *b)
{
    unsigned int *element = (unsigned int *)a;
    unsigned int *anotherElement = (unsigned int *)b;
    int compareValue = element[1] - anotherElement[1];
    if (compareValue == 0)
    {
        return element[0] - anotherElement[0];
    }
    return compareValue;
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
