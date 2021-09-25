/**
 *  Programa de prueba para la búsqueda Fibonacci
 *  @author @MarcoLg23 Marco Antonio Lavarrios González
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc fib.c ../tiempo.c -o fib
 *  Ejecución: ./fib n < ../../../numeros10millones.txt
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;                          // TMAÑO DE LA SECUENCIA
int *arrfib;                    // ARREGLO PARA CADA VALOR
int i;                          

void *runn(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("el formato es: ./fib <valor>\n");
        return -1; //ERROR
    }

    if (atoi(argv[1]) < 0)
    {
        printf("%d debe ser>0\n", atoi(argv[1]));
        return -1; //ERROR
    }

    n = atoi(argv[1]);
    arrfib = (int *)malloc(n * sizeof(int)); //TAMAÑO DEL ARREGLO
    pthread_t *threads = (pthread_t *) malloc(n * sizeof(pthread_t)); //TAMAÑO DEL ARREGLO DE HILOS
    pthread_attr_t attr; //ATRIBUTO DEL HILO

    pthread_attr_init(&attr);

    for (i=0; i<n; i++)
    {
        pthread_create(&threads[i], &attr, runn, NULL);
    }                           //CREACIÓN DE HILOS

    int j;

    for (j = 0; j < n; j++)
    {
        pthread_join(threads[j], NULL);
    }
    
    printf("Secuencia Fibonacci:");
    int k;

    for (k = 0; k < n; k++)
    {
        printf("%d,", arrfib[k]);
    }                           // End of printing arrfib.
    return 0;
}                               // End of main.

void *runn(void *arg)
{
    if (i == 0)
    {
        arrfib[i] = 0;
        pthread_exit(0);
    }                           // first fib term

    if (i == 1)
    {
        arrfib[i] = 1;
        pthread_exit(0);
    }                           // seconed fib term
    else
    {
        arrfib[i] = arrfib[i - 1] + arrfib[i - 2];
        // printf("arrfib[%d]%d,\n",i,arrfib[i]);
        pthread_exit(0);        // thread exit.
    }                           // End of else
}















/*
// C program for Fibonacci Search
#include <stdio.h>

// Utility function to find minimum of two elements
int min(int x, int y) { return (x <= y) ? x : y; }

int fibMonaccianSearch(int arr[], int x, int n)
{
	int fibMMm2 = 0; // (m-2)'th Fibonacci No.
	int fibMMm1 = 1; // (m-1)'th Fibonacci No.
	int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

	while (fibM < n) {
		fibMMm2 = fibMMm1;
		fibMMm1 = fibM;
		fibM = fibMMm2 + fibMMm1;
	}

	// Marks the eliminated range from front
	int offset = -1;
	while (fibM > 1) {
		// Check if fibMm2 is a valid location
		int i = min(offset + fibMMm2, n - 1);
		if (arr[i] < x) {
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		}
		else if (arr[i] > x) {
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		}
		else
			return i;
	}
	if (fibMMm1 && arr[offset + 1] == x)
		return offset + 1;
	return -1;
}

int main(void)
{
	int arr[]
		= { 10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100,235};
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 235;
	int ind = fibMonaccianSearch(arr, x, n);
if(ind>=0)
	printf("Found at index: %d",ind);
else
	printf("%d isn't present in the array",x);
	return 0;
}*/