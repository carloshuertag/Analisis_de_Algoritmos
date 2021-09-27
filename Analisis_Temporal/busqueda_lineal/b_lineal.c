/**
 *  @author @Angel Alan Hernandez Dominguez
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición tiempo de busqueda lineal
 *  Compilación: 
 *  Ejecución: 


 //TO DO IMPLEMENTAR LOS CONTADORES
*/

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2
#define N_VECES 1 //Numero de iteraciones para encontrar el caso medio
#define HILOS_A_USAR 5

void* busqueda_lineal(void* arg);

//Indice donde se encontro el elemento (se se encontro)
int index = NO_ECNONTRADO;
//Numero de hilo, lo usa cada hilo para resolver el subarreglo que le toca.
int numero_hilo = 0;
//Arreglo que tendra los elementos
int* A = NULL;
//Tamanio del arreglo
int n;
//Elemento buscado
int buscado;

int main(int argc, char* argv[]) {
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
        //Lee el elemento a buscar
        scanf("%d", &buscado);

        //Crwa los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_create(&hilos[i], NULL, busqueda_lineal, (void*)NULL);

        //Espera a que terminen todos los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_join(hilos[i], NULL);

        if(index == NO_ENCONTRADO)
            printf("Elemento no encontrado\n");
        else
            printf("Elemento encontrado en la posicion: %d\n", index);
    }

    return 0;
}

/**
 * @param A arreglo de enteros
 * @param tam tamanio del arreglo
 * @param buscado es el elemento buscado en el arreglo
 * @returns index del elemento buscado o NO_ECNONTRADO
 */
// int busqueda_lineal(int* A, int tam, int buscado){
//     if(A == NULL){
//         perror("Apuntador invalido");
//         return ERR;
//     }

//     int i = 0;
//     while(i < tam && A[i] != buscado)
//         i++;

//    return i < tam ? i : NO_ECONTRADO;
// }

/** 
 * @param arg argumento para pasar datos al hilo. En esta implemetancion no se ocupa
*/
void* busqueda_lineal(void* arg){
    if(A == NULL){
	    perror("Apuntador invalido");
	    return ERR;
    }

    //Obtiene su bunero de hilo
    int numero_hilo_local = numero_hilo++;
    //Obtiene la posicion desde la que debe emepezar a buscar
    int inicio = numero_hilo_local * n / HILOS_A_USAR;
    //Obtiene la posicion desde la que debe dejar de buscar
    int fin = (numero_hilo_local + 1) * n / HILOS_A_USAR;
    
    while(inicio < fin && index == NO_ENCONTRADO){
        if(A[inicio] == buscado)
            index = inicio
        
        inicio++;
    }
}