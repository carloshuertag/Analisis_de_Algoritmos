/**
 *  Programa de prueba para la búsqueda Fibonacci
 *  @author @MarcoLg23 Marco Antonio Lavarrios González
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc fibhilos.c ../tiempo.c -o fibhilos -lpthread -lm
 *  Ejecución: ./fibhilos n x < 10millonesOrd.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../tiempo.h"
#include <math.h>

int *A;
int i;
int NumThreads;
double utime0, stime0, wtime0, utime1, stime1, wtime1;

struct args {
    int *A;
    int n;
    int x;
    int li;
    int id;
};

void* fibo(void* args);
int fibonacci(int A[], int x, int n);

int main (int argc, char* argv[]){

    int x = 2147483528;
    //Declaracion de variables del main
    int n; //n determina el tamaño del algoritmo dado por argumento al ejecutar
    int i; //Variables para loops
    /*Recepción y decodificación de argumentos*/
    if(argc!=3){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución, tamano arreglo=n y número de hilos)
        printf("\nIndique el tamano del arreglo - Ejemplo: %s 100 4\n",argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del algoritmo y el tercero como numero a buscar
    else
    {
        n=atoi(argv[1]);
        A = (int*)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
        NumThreads = atoi(argv[3]);
    }
    if(n < NumThreads){
        printf("\nLos numeros de hilos deben ser menor al tamaño del arreglo %d < %d \n",n, NumThreads);
        exit(1);
    }
    if (A == NULL) {
        perror("Espacio de memoria no asignado\n");
        exit(1);
    }
    for(i = 0; i < n; i++)
        scanf("%d", &A[i]); // llenando el arreglo
    
    /*Parte de hilos*/       
    pthread_t *thread;
    thread = malloc(NumThreads*sizeof(pthread_t));
   	
   	int subn = n/NumThreads;
    uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
    for (i=0; i<NumThreads; i++){
    	//Asignación de datos
        struct args *datos = (struct args *)malloc(sizeof(struct args));
    	datos->n = subn;
        datos->x = x;
        
        datos->li = ceil(1.0*(n/NumThreads)*i);
        datos->A = &A[datos->li];
        if(i==NumThreads-1){
            datos->n = n-datos->li;
        }
        datos->id = i;
    	if (pthread_create (&thread[i], NULL, fibo,(void*)datos) != 0 ){
    		perror("El thread no  pudo crearse");
    		exit(-1);
    	}
    }
	for (i=0; i<NumThreads; i++) 
        pthread_join (thread[i], NULL);
    printf("%d threads (Tiempo de procesamiento aproximado por cada thread en CPU) %.10f s\n", NumThreads,(utime1 - utime0)/NumThreads);
   free(A);
   return 0;
}

void* fibo(void* dato){
    struct args *datos = dato;
	int res = fibonacci(datos->A, datos->x, datos->n);
	
	(res == -1)? printf("\nHola\tSoy el thread %d y no encontre el elemento \n", datos->id+1)
                 : printf("\nHola\tSoy el thread %d y el elemento se encuentra en el indice %d \n",datos->id+1, datos->li + res);
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
    printf("\n");
    printf("nHola\tSoy el thread %d, tiempos: real (Tiempo total)  %.10f s\n user (Tiempo de procesamiento en CPU's) %.10f s\n",  datos->id+1, wtime1 - wtime0, utime1 - utime0);

    /*printf("sys (Tiempo en acciónes de E/S)  %.3f s\n",  stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");*/
}

int min(int x, int y)
{
    return (x <= y) ? x : y;
}

int fibonacci(int A[], int x, int n)
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
		if (A[i] < x) {
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		}
		else if (A[i] > x) {
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		}
		else
			return i;
	}
	if (fibMMm1 && A[offset + 1] == x)
		return offset + 1;
	return -1;
}