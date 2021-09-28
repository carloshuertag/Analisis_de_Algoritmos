/**
 *  @author @Angel Alan Hernandez Dominguez
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición tiempo de busqueda binaria
 *  Compilación: gcc b_binaria_hilos.c tiempo.c -o bbh -lpthread
 *  Ejecución: ./bbh n < 10millones.txt

 //TO DO IMPLEMENTAR LOS CONTADORES
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../tiempo.h"

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2

#define HILOS_A_USAR 5

void* busqueda_binaria(void* arg);

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

    for(int i = 0; i < 20; i++){
        //REINICIA VALORES GLOBALES
        posicion = NO_ENCONTRADO;
        buscado = buscados[i];
        numero_hilo = 0;
        
        uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
        //Crwa los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_create(&hilos[i], NULL, busqueda_binaria, (void*)NULL);

        //Espera a que terminen todos los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_join(hilos[i], NULL);

        // printf("%d ", buscados[i]);
        // if(posicion == NO_ENCONTRADO)
        //     printf("Elemento no encontrado\n");
        // else
        //     printf("Elemento encontrado en la posicion: %d\n", posicion);
        
        uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
        avg += wtime1 - wtime0; // acumular el tiempo real
        stime0 = stime1 = utime0 = utime1 = wtime0 = wtime1 = 0.0; // reiniciar
    }
    avg /= 20; // promediar el tiempo real
    printf("\nBinaria hilos: n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(A);

    return 0;
}

/**
 * @param arg argumento para pasar datos al hilo. En esta implemetancion no se ocupa
*/
void* busqueda_binaria(void* arg){
    if(A == NULL){
	    perror("Apuntador invalido");
	    exit(1);
    }
    
    int numero_hilo_local = numero_hilo++;
    //Busqueda binaria  
    int inferior = numero_hilo_local * n / HILOS_A_USAR; 
    int superior = (numero_hilo_local + 1) * n / HILOS_A_USAR;
    int mitad = ((superior - inferior) >> 1) + inferior;

    while(inferior <= superior && posicion == NO_ENCONTRADO){
    	if( A[mitad] == buscado )
            posicion = mitad;
        else if(A[mitad] > buscado)
	        superior = mitad - 1;
	    else 
	        inferior = mitad + 1;

	    mitad = ((superior - inferior) >> 1) + inferior;
        // printf("inferior: %d superior: %d num mitad: %d \n", inferior, superior, A[mitad]);
    }
}
