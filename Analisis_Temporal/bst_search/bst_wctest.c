/**
 *  Programa de prueba para la búsqueda por árbol (iterativa)
 *  @author @huerta2502 Carlos Huerta García
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc bst_wctest.c ../tiempo.c -o bst_wctest
 *  Ejecución: ./bst_wctest n < ../../../10millones.txt
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst_entry.h" // entrada del árbol binario de búsqueda
#include "bst.h" // árbol binario de búsqueda
#include "../tiempo.h" // mediciones de tiempo

int main(int argc, char **argv){
    register unsigned int n, i; // longitud del arreglo e iterador
    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0.0; //para los tiempos
    Entry item = 2147483528; //elemento que no se encuentra y es mayor al último (wc)
    if (argc != 2)
    {
        fprintf(stderr, "\nPlease enter the array length, e.g.: %s 100000\n",
                argv[0]);
        exit(1);
    }
    else
        n = atoi(argv[1]); // Toma del argumento la longitud del arreglo
    int *arr = (int *)malloc(n * sizeof(int)); // asigna la memoria para el arreglo
    if (arr == NULL)
    {
        perror("Memory not allocated.\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]); // guarda los elemetos introducidos en el arreglo
    Node root = insertNode(arr[0], NULL); //se crea el nodo raíz
    for (i = 1; i < n; i++)
        insertNode(arr[i], root); // se crea el árbol con los elemntos de arr
    uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
    searchKey(root, item); // busca item en el árbol
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
    avg += wtime1 - wtime0; // acumular el tiempo real
    printf("\nBST Search for n = %d\nAvergae real time: %.10e s\n", n, avg);
    deleteTree(root);
    free(arr);
    exit(0);
}