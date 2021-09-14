/**
 *  Programa de prueba para el ordenamiento shell
 *  @author @huerta2502 Carlos Huerta García
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc shell_sort_test.c ../tiempo.c -o shell_sort_test
 *  Ejecución: ./shell_sort_test n < ../../../numeros10millones.txt
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "shell_sort.h" // ordenamiento shell
#include "../tiempo.h" // mediciones de tiempo

int main(int argc, char **argv)
{
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //para los tiempos
    int n; // longitud del arreglo
    register unsigned int i; // iterador
    if (argc != 2)
    {
        fprintf(stderr, "\nPlease enter the array length, e.g.: %s 1000\n",
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
    uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
    shellSort(arr, n); // ordenamiento shell
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
    printf("\nn=%d\nreal (Tiempo total)  %.10e s\n", n, wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",
            utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n",
           100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");
    free(arr);
    exit(0);
}