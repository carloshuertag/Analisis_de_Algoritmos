/**
 *  Programa de prueba para la búsqueda Fibonacci
 *  @author @MarcoLg23 Marco Antonio Lavarrios González
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc fibhilos.c ../tiempo.c -o fibhilos -lpthread -lm
 *  Ejecución: ./fibhilos tamañoarreglo < 10millonesOrd.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../tiempo.h"
#include <math.h>

int *A;
int i;
int NumThreads = 4;
double utime0, stime0, wtime0, utime1, stime1, wtime1, avg;

#define N_Veces 20

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

    int numBuscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644,
                        1295390003, 450057883,  18765041, 1980098116, 152503, 5000,
                        1493283650, 214826, 1843349527, 1360839354, 2109248666,
                        2147470852, 0};
    //Declaracion de variables del main
    int n; //n determina el tamaño del algoritmo dado por argumento al ejecutar
    int i; //Variables para loops
    /*Recepción y decodificación de argumentos*/
    if(argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución, tamano arreglo=n)
        printf("\nIndique el tamano del arreglo - Ejemplo: %s 100 4\n",argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del algoritmo y el tercero como numero a buscar
    else
    {
        n=atoi(argv[1]);
    }
    A = (int*)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
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
       for (int j =0; j<N_Veces;j++){
        int x = numBuscar[j];
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
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
        avg += wtime1 - wtime0; // acumular el tiempo real
        stime0 = stime1 = utime0 = utime1 = wtime0 = wtime1 = 0.0; // reiniciar
    }
    avg /= N_Veces; // promediar el tiempo real
    printf("\nBusqueda fibonacci_hilos con n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(A);
    exit(0);
   return 0;
}

void* fibo(void* dato){
    struct args *datos = dato;
	fibonacci(datos->A, datos->n, datos->x);
	pthread_exit(NULL);
}

int min(int x, int y)
{
    return (x <= y) ? x : y;
}

/**
 *  Busca un numero x en un arreglo de tamaño n usando el algoritmo de busqueda exponencial
 *  @param A arreglo de tamaño n
 *  @param n tamaño del arreglo
 *  @param x numero a buscar
 *  @return la posicion de la primera ocurrencia de x en el arreglo
*/
int fibonacci(int A[], int n, int x)
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