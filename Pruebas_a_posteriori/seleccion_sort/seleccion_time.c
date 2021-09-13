/**
 *  @author @Reina Beatriz Juarez Leonel
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición de tiempo del ordenamiento usando el algoritmo de seleccion en C y recepción de parametros en C
 *  Compilación: "gcc seleccion_time.c ../tiempo.c -o seleccion"
 *  Ejecución: "./seleccion n < ../../../numeros10millones.txt"
*/

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"

//DECLARACIÓN DE FUNCIONES
void seleccion(int* A, int n); //Función de ordenamiento tomando como parametro un arreglo y el tmño del mismo (Indexado desde 0)

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
	for(i = 0; i < n; i++)
        	scanf("%d", &arreglo[i]); // llenando el arreglo
        
        /*Medicion de tiempos*/
        	
	uswtime(&utime0, &stime0, &wtime0); //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	seleccion(arreglo, n); //Llamando al Algoritmo
	uswtime(&utime1, &stime1, &wtime1); //Evaluar los tiempos de ejecución 
	
	//Mostrar los tiempos calculados en formato exponecial
	printf("\n");
    printf("\nn=%d\nreal (Tiempo total)  %.10e s\n", n, wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	exit (0); //Termino del programa
}

/**
 *  Ordena un arreglo de tamaño n usando el algoritmo de seleccion
 *  @param A arreglo a ordenar
 *  @param n tamaño del arreglo
*/
//DEFINICIÓN DE FUNCIONES 
void seleccion(int *A, int n){
	int p, k, temp;
	for(int k=0; k<n-2; k++){
		p=k;
		for (int i=k+1; i<n-1; i++){
			if(A[i]<A[p])
				p=i;
		}
		temp = A[p];
		A[p] = A[k];
		A[k] = temp;
	}
}
