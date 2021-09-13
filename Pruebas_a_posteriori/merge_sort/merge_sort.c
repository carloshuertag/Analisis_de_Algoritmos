#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"

//Declaración de variables
int n;

//Declaracion de funciones
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);

int main(int argc, char *argv[])
{
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //para los tiempos
	register unsigned int i; // iterador
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
    mergeSort(arr, 0, n - 1); // merge sort
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
 *  Ordena el subarreglo de arr en l a r.
 *  @param arr arreglo del que se obtiene el subarreglo.
 *  @param l índice izquierdo del subarreglo.
 *  @param r índice derecho del subarreglo.
*/
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/** 
 *  Mezcla dos subarreglos de un arr.
 *  @param arr arreglo original
 *  @param l índice izquierdo del primer subarreglo.
 *  @param m índice derecho del primer subarreglo.
 *  @param r índice derecho del segundo subarreglo.
*/
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
