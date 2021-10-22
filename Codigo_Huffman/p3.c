#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "p3h.h"

int compareTo(const void *a, const void *b);
void traverseInOrder(Node root, int code);
int getBitsCount(int n);

int codes[256];


/** 
 *  conversion de un numero decimal a binario
 *  @param dec numero en decimal.
 *  @param tam bits que ocupa el numero decimal.
 *  @param arr arreglo donde se coloca el numero en binario.
*/
void DecToBin(int dec, int tam, char* arr) {
    int  aux=1;
    for(int i=tam-1;i>=0;i--){
        arr[i] = dec&aux? 1:0;
        aux*=2; 
    }
}

/** 
 *  Impresión de numero decimal, formando bytes
 *  @param dec numero en decimal.
*/
void printByte(int dec) {
    int tam = 8;
    char* arr = malloc(sizeof(char) * tam);
    DecToBin( dec, tam, arr);
    for(int i=0;i<tam;i++){
        printf("%d", arr[i]);
    }
}

/** 
 *  impresion de numeros binarios (dentro se ocupa DecToBin)
 *  @param dec numero en decimal.
*/
void printDecToBin(int dec) {
    /*if(dec > 1){
        printDecToBin(dec>>1);
    }
    printf("%d", dec&1);*/
    int tam = getBitsCount(dec);
    char* arr = malloc(sizeof(char) * tam);
    DecToBin( dec, tam, arr);
    for(int i=0;i<tam;i++){
        printf("%d", arr[i]);
    }
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
    qsort(elements, elementsSize, 2 * sizeof(unsigned int), compareTo);
    for (j = 0; j < elementsSize; j++)
    {
        printf("\n0x%02x\t%d", elements[j][0], elements[j][1]);
    }
    Node tree = createTree(elements, elementsSize);
    memset(codes, -1, 256 * sizeof(int)); //initialize codes in -1
    traverseInOrder(tree, 0);
    long outputSize = 0;
    for(j = 0; j < 256; j++)
    {
        if(codes[j] != -1)
        {
            outputSize += getBitsCount(codes[j]) * frequencies[j];
            printf("\n0x%02x: code: (0x%02x) ", j, codes[j]);
            printDecToBin(codes[j]);

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
    printf("\n");
    int tamSalBytes = (int)ceil((double)outputSize/8.0); //Numero de bytes 
    unsigned char *output = calloc(tamSalBytes, sizeof(unsigned char));
    unsigned char *auxOutput = calloc((int)ceil((double)outputSize), sizeof(unsigned char)); //Auxiliar de output
    memset(output, 0, tamSalBytes * sizeof(char)); //estableciendo output en ceros
    memset(auxOutput, 0, outputSize* sizeof(char)); //estableciendo auxOutput en ceros
    int offset = 0;
    unsigned int k = 0;
   
    /*Llenando arreglo de bits*/
    for(i = 0; i < fileSize; i++)
    { // reads file byte to byte
        int aux=codes[buffer[i]];
        int tam = getBitsCount(aux);
        char* arr = malloc(sizeof(char) * tam);
        DecToBin( aux, tam, arr);
        for(int j=0;j<tam;j++){
            auxOutput[offset+j] = arr[j];
            
        }
        offset+=tam;

       // byteToWrite(output, codes[buffer[i]], &offset, &k);
    }

    /*Acomodando en bytes*/
    for(i=0; i<tamSalBytes; i++){
        for(j=0; j<8 && i*8+j<outputSize; j++){
                if(auxOutput[i*8+j]){
                    output[i]+=pow(2,7-j);
                }
        }
    }
    
    printf("Salida\n");
    for(i=0; i<tamSalBytes; i++){
        printByte(output[i]);
    }

    printf("\nAuxiliar\n");
    for(i=0; i<outputSize; i++){
        printf("%d", auxOutput[i]);
    }
    printf("\n");

            
    //printf("0x%02x\t", buffer[i]);

    fwrite(output, sizeof(output[0]), outputSize, codedFile);
    fclose(codedFile);
    printf("\n");
    /*for(i = 0; i < outputSize; i++)
    {
        printDecToBin(output[i]);
    }*/
    free(output);
    free(buffer);
    return 0;
}

int getBitsCount(int n)
{
    return (n == 0) ? 1 : ((int)log2(n) + 1);
}

/**
 *  compare function for qsort stdlib implementation.
 *  @param a element to compare
 *  @param b next element to compare
 *  @return comparisson according to qsort doc.
*/
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
