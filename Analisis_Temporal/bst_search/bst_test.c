/**
 *  Programa de prueba para la búsqueda por árbol (iterativa)
 *  @author @huerta2502 Carlos Huerta García
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc bst_test.c ../tiempo.c -o bst_test
 *  Ejecución: ./bst_test n < ../../../numeros10millones.txt
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst_entry.h" // entrada del árbol binario de búsqueda
#include "bst.h" // árbol binario de búsqueda

int main(int argc, char **argv){
    int n;                   // longitud del arreglo
    register unsigned int i; // iterador
    bool found;
    Entry item;
    if (argc != 3)
    {
        fprintf(stderr, "\nPlease enter the array length, e.g.: %s 10000 123456\n",
                argv[0]);
        exit(1);
    }
    else
    {
        n = atoi(argv[1]); // Toma del argumento la longitud del arreglo
        item = atoi(argv[2]); // item to search on array
    }
    int *arr = (int *)malloc(n * sizeof(int)); // asigna la memoria para el arreglo
    if (arr == NULL)
    {
        perror("Memory not allocated.\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]); // guarda los elemetos introducidos en el arreglo
    Node root = insertNode(arr[0], NULL);
    for (i = 1; i < n; i++)
        insertNode(arr[i], root);
    found = searchKey(root, item);
    printf((found)? "\nitem was found": "\nitem does not exists");
    free(arr);
    exit(0);
}