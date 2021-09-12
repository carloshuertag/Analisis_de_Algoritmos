/**
 *  @author @Reina Beatriz Juarez Leonel
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición de tiempo del ordenamiento usando el algoritmo de insercion en C y recepción de parametros en C
 *  Compilación: "gcc insercion_time.c ../tiempo.c -o insercion"
 *  Ejecución: "./insercion n < ../numeros10millones.txt"
*/

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

//DECLARACIÓN DE FUNCIONES
/**
 *  Ordena un arreglo de tamaño n usando el algoritmo de insercion
 *  @param A arreglo a ordenar
 *  @param n tamaño del arreglo
*/
void insercion(int* A, int n); //Función de ordenamiento tomando como parametro un arreglo y el tmño del mismo (Indexado desde 0)

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){
	//Declaracion de variables del main
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n; //n determina el tamaño del algorito dado por argumento al ejecutar
	int i; //Variables para loops
	
	/*Recepción y decodificación de argumentos*/
	if(argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
		printf("\nIndique el tamaño del arreglo - Ejemplo: %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else{
		n=atoi(argv[1]);
	}
	int *arreglo = (int*)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
    	if (arreglo == NULL) {
		perror("Espacio de memeria no asignado\n");
		exit(1);
	    }
	for(int i = 0; i < n; i++)
        	scanf("%d", &arreglo[i]); // llenando el arreglo
        
        /*Medicion de tiempos*/
        	
	uswtime(&utime0, &stime0, &wtime0); //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	insercion(arreglo, n); //Llamando al Algoritmo
	uswtime(&utime1, &stime1, &wtime1); //Evaluar los tiempos de ejecución 
	
	//Mostrar los tiempos calculados en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	exit (0); //Termino del programa
}

//DEFINICIÓN DE FUNCIONES 
void insercion(int *A, int n){
	for(int i=0; i<n-1; i++){
		int j=i;
		int temp = A[i];
		while(j>0 && temp<A[j-1]){
			A[j] = A[j-1];
			j--;
		}
		A[j] = temp;	
	}
}
