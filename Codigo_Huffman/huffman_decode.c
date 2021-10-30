/**
 *  @author @huerta2502 - Carlos Huerta Garcia
 *          @angel-hache-de - Angel
 *          @MarcoLg23 - Marco Lavarrios
 *          @ReinaLeonel - Reina Beatriz Juarez Leonel
 *  Curso: Analisis de algoritmos  3CM13
 *  (C) Octubre 2021
 *  @version 1.0
 *  ESCOM-IPN
 *  Decodificación de un archivo .dat codificado con el alglritmo de Hufffman
 *  Dado un archivo auixiliar con la tabla de frecuencias de los bytes originales.
 *  Compilación: gcc huffman_decode.c tiempo.c -o huffman_decode
 *  Ejecución: ./huffman_decode filePath auxFilePath
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman_tree.h"
#include "huffman_code.h"
#include "tiempo.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    { // usage error
        fprintf(stderr, "Usage: ./%s <file path> <aux file path>\n", argv[0]);
        return 1;
    }
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // time meassure
    uswtime(&utime0, &stime0, &wtime0); // start time meassure
    FILE *auxFilePtr = fopen(argv[2], "r"); // open aux file
    if (!auxFilePtr)
    { // error opening file
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[2]);
        return 1;
    }
    unsigned int elements[256][2] = {{0}, {0}},
                elementsSize = 0, fileSize;
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
        { // last metadata at the end of file
            fscanf(auxFilePtr, "%u", &fileSize);
            fscanf(auxFilePtr, "%s", extension);
            break;
        }
        else
        { // read frequency
            fscanf(auxFilePtr, "%u", &elements[elementsSize][1]);
            elementsSize++;
        }
    }
    fclose(auxFilePtr);
    Node root = buildTree(elements, elementsSize); // Huffman tree for codes
    FILE* encodedFilePtr = fopen(argv[1], "rb"); //open file in binary read
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
    stripExtension(filePath, argv[2]); // argv[2] as aux to store ".dat"
    strcat(filePath, extension); // add og extension
    free(extension); // extension no longer needed
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
    Node node; // tree node to traverse
    unsigned int j, i;
    short bitOffset = 7; // bits range from 7 to 0
    for(i = 0, j = 0; i < fileSize; i++){
        node = root; // reset node to root
        while(node->byte == NOITEM){ // while node is internal
            if(getBitAt(buffer[j], bitOffset--))
                node = node->right; // go right
            else // go left
                node = node->left;
            if( bitOffset < 0  ){ bitOffset = 7; j++; }
        }
        output[i] = node->byte;
    }
    fwrite(output, sizeof(output[0]), fileSize, filePtr);
    fclose(filePtr); // write decoded file and close it
    uswtime(&utime1, &stime1, &wtime1); // stop time meassure
    printf("\nHuffman decoded file: %s\n", filePath);
    printf("\nn=%u\nreal (total time)  %.10e s\n", fileSize, wtime1 - wtime0);
	printf("user (CPU time) %.10e s\n",  utime1 - utime0);
	printf("sys (E/S time)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall: %.10f %% \n",
            100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\nCompression OG vs Compressed: %u %u %f %%\n", fileSize,
            encodedFileSize, 100.0 * (double)fileSize / (double)encodedFileSize);
    free(filePath);
    freeTree(root);
    root = NULL;
    free(buffer);
    free(output);
    return 0; // success
}
