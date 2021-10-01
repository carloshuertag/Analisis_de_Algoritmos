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
#include <pthread.h>

int *arr;
int i;

void *runn(void *arg);

int min(int x, int y) {
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
    //Declaracion de variables del main
    int n; //n determina el tamaño del algoritmo dado por argumento al ejecutar
    int x; //x numero a buscar dado por el argumento
    int i; //Variables para loops

    /*Recepción y decodificación de argumentos*/
    if(argc!=3){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
        printf("\nIndique el tamano del arreglo y el numero a buscar - Ejemplo: %s 100 5\n",argv[0]);
        exit(1);
    } 
    //Tomar el segundo argumento como tamaño del algoritmo y el tercero como numero a buscar
    else{
        n=atoi(argv[1]);
        x=atoi(argv[2]);
    }
    arr = (int*)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
    pthread_t *threads = (pthread_t *) malloc(n * sizeof(pthread_t)); //TAMAÑO DEL ARREGLO DE HILOS
    pthread_attr_t attr; //ATRIBUTO DEL HILO
        if (arr == NULL) {
        perror("Espacio de memoria no asignado\n");
        exit(1);
        }
    for(i = 0; i < n; i++)
            scanf("%d", &arr[i]); // llenando el arreglo

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
        printf("%d,", arr[k]);
    }
    return 0;

    int ind = fibonacci(arr, x, n);
    if(ind>=0)
	printf("Found at index: %d",ind);
    else
	printf("%d isn't present in the array",x);
	return 0;
}
void *runn(void *arg)
{
    if (i == 0)
    {
        arr[i] = 0;
        pthread_exit(0);
    }                           //PRIMER TERMINO

    if (i == 1)
    {
        arr[i] = 1;
        pthread_exit(0);
    }                           //SEGUNDO TERMINO
    else
    {
        arr[i] = arr[i - 1] + arr[i - 2];
        printf("arr[%d]%d,\n",i,arr[i]);
        pthread_exit(0);
    }
}