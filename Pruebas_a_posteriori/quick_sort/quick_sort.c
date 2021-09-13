#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"

//Declaración de variables
int i, j, n;

//Declaracion de funciones
void quickSort(int *arr, int l, int h);
int pivote(int *A, int p, int r);
void intercambiar(int *A, int i, int j);

int main(int argc, char *argv[])
{
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //para los tiempos
    if (argc!=2) 
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
    quickSort(arr, 0, n - 1);
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

/**
 *  Implementación de ordenamiento rápido.
 *  @param arr arreglo a ordenar.
 *  @param l índice de partida.
 *  @param h índice de termino.
*/
void quickSort(int *arr, int l, int h)
{
    if (l < h)
    {
        int pi = pivote(arr, l, h);
        quickSort(arr, l, pi - 1);
        quickSort(arr, pi + 1, h);
    }
}

/**
 *  Toma el último elemento como pivote, 
 *  coloca el pivote en la posición del arreglo
 *  ordenado, y coloca los más pequeños
 *  que el pivote a su izquierda y
 *  los más grandes que el pivote
 *  a su derecha.
 *  @param arr arreglo a ordenar.
 *  @param l índice de partida.
 *  @param h índice de termino.
*/
int pivote(int *arr, int l, int h)
{
    int piv = arr[h];
    i = l - 1;
    j = l;

    //
    for (j = l; j <= h - 1; j++)
    {
        if (arr[j] < piv)
        {
            i++;
            intercambiar(arr, i, j);
        }
    }
    intercambiar(arr, i + 1, h);
    return (i + 1);
    //
}
/**
 *  Una función util para intercambiar dos elementos en un arreglo.
*/
void intercambiar(int *arr, int i, int j)
{
    int temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}