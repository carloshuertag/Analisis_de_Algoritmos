/**
 *  @author @Angel Alan Hernandez Dominguez
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición tiempo de busqueda lineal
 *  Compilación: gcc b_lineal_hilos.c tiempo.c -o blh -lpthread
 *  Ejecución: ./blh 100000 < 10millones.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../tiempo.h"

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2
#define N_VECES 20 //Numero de iteraciones para encontrar el caso medio
#define HILOS_A_USAR 5

void* busqueda_lineal(void* arg);

//Indice donde se encontro el elemento (se se encontro)
int posicion = NO_ENCONTRADO;
//Numero de hilo, lo usa cada hilo para resolver el subarreglo que le toca.
int numero_hilo = 0;
//Arreglo que tendra los elementos
int* A = NULL;
//Tamanio del arreglo
int n;
//Elemento buscado
int buscado;

int main(int argc, char* argv[]) {
    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0; //para los tiempos
    int buscados[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644,
                    1295390003, 450057883,  18765041, 1980098116, 152503, 5000,
                    1493283650, 214826, 1843349527, 1360839354, 2109248666,
                    2147470852, 0};

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
    
    //Hilos
    pthread_t hilos[HILOS_A_USAR];
    //Llena el arreglo
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for(int i = 0; i < N_VECES; i++){
        //Indice donde se encontro el elemento (se se encontro)
        posicion = NO_ENCONTRADO;
        //Numero de hilo, lo usa cada hilo para resolver el subarreglo que le toca.
        numero_hilo = 0;
        buscado = buscados[i];

        uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
        
        //Crea los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_create(&hilos[i], NULL, busqueda_lineal, (void*)NULL);

        //Espera a que terminen todos los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_join(hilos[i], NULL);

        uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
        avg += wtime1 - wtime0; // acumular el tiempo real
        stime0 = stime1 = utime0 = utime1 = wtime0 = wtime1 = 0.0; // reiniciar
        
        // printf("%d ", buscados[i]);
        // if(posicion == NO_ENCONTRADO)
        //     printf("Elemento no encontrado\n");
        // else
        //     printf("Elemento encontrado en la posicion: %d\n", posicion);
    }
    avg /= 20; // promediar el tiempo real
    printf("\nLineal hilos: n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(A);

    return 0;
}

/** 
 * @param arg argumento para pasar datos al hilo. En esta implemetancion no se ocupa
*/
void* busqueda_lineal(void* arg){
    if(A == NULL){
	    perror("Apuntador invalido");
	    exit(1);
    }

    //Obtiene su bunero de hilo
    int numero_hilo_local = numero_hilo++;
    //Obtiene la posicion desde la que debe emepezar a buscar
    int inicio = numero_hilo_local * n / HILOS_A_USAR;
    //Obtiene la posicion desde la que debe dejar de buscar
    int fin = (numero_hilo_local + 1) * n / HILOS_A_USAR;
    
    while(inicio < fin && posicion == NO_ENCONTRADO){
        if(A[inicio] == buscado)
            posicion = inicio;
        
        inicio++;
    }
}