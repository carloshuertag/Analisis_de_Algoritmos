/**
 *  Programa de prueba para la búsqueda Fibonacci
 *  @author @MarcoLg23 Marco Antonio Lavarrios González
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc fib.c ../tiempo.c -o fib
 *  Ejecución: ./fib n x < 10millonesOrd.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2

int *arr;
int i;

int min(int x, int y)
{
    return (x <= y) ? x : y;
}

int fibonacci(int arr[], int x, int n)
{
	int fibMMm2 = 0;
	int fibMMm1 = 1;
	int fibM = fibMMm2 + fibMMm1;

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

int main (int argc, char* argv[]){

    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0; //para los tiempos
    int buscado = 2147483528;
    //Declaracion de variables del main
    int n; //n determina el tamaño del algoritmo dado por argumento al ejecutar
    int i; //Variables para loops
    /*Recepción y decodificación de argumentos*/
    if(argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
        printf("\nIndique el tamano del arreglo - Ejemplo: %s 100\n",argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del algoritmo y el tercero como numero a buscar
    else
        n=atoi(argv[1]);
    arr = (int*)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
    if (arr == NULL) {
        perror("Espacio de memoria no asignado\n");
        exit(1);
    }
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]); // llenando el arreglo
    uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
    int posicion = fibonacci(arr, buscado, n); //Busca el elemento
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
    avg += wtime1 - wtime0; // acumular el tiempo real
    printf("\nFibonacci con n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(arr);
	return 0;
}