/**
 *  @author @Angel Alan Hernandez Dominguez
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición tiempo de busqueda lineal
 *  Compilación: gcc b_lineal_wc.c -o blwc
 *  Ejecución: ./blwc 1000000 < 10millones.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h" // mediciones de tiempo

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2

int busqueda_lineal(int* A, int tam, int buscado);

int main(int argc, char* argv[]) {
    register int n, i; // tamaño de problema e iterador
    int* A; //arreglo en donde se busca
    int buscado = 2147483528; //elemento que no se encuentra y es mayor al último (wc)
    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0.0; //para los tiempos
    //Recepción y decodificación de argumentos
    if (argc!=2){ //Se espera el valor n
		printf("\nIngrese el # de números a ordenar: \n");
		exit(1);
	} 
	//Se obtiene el valor de n.
	else
		n=atoi(argv[1]);

    A = (int*)malloc(n*sizeof(int));
    if(A == NULL){
        perror("Error con malloc");
        exit(1);
    }
    //Llena el arreglo
    for(i = 0; i < n; i++)
        scanf("%d", &A[i]);
    i = 0;
    uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
    int posicion = busqueda_lineal(A, n, buscado); //Busca el elemento
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
    avg += wtime1 - wtime0; // acumular el tiempo real
    printf("\n Lineal con n = %d\nTiempo real: %10e\n", n, avg);
    free(A);
    return 0;
}

/**
 * @param A arreglo de enteros
 * @param tam tamanio del arreglo
 * @param buscado es el elemento buscado en el arreglo
 * @returns index del elemento buscado o NO_ECNONTRADO
 */
int busqueda_lineal(int* A, int tam, int buscado){
    if(A == NULL){
        perror("Apuntador invalido");
        return ERR;
    }

    int i = 0;
    while(i < tam && A[i] != buscado)
        i++;

    return i < tam ? i : NO_ENCONTRADO;
}