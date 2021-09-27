/**
 *  @author @Angel Alan Hernandez Dominguez
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición tiempo de busqueda binaria
 *  Compilación: 
 *  Ejecución: 

 //TO DO IMPLEMENTAR LOS CONTADORES
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2

#define HILOS_A_USAR 5

void* busqueda_binaria(void* arg);
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

    double contadores = [0, 0, 0, 0, 0];

    double contador_global = 0;
    double contador_reseteable = 0;

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
            pthread_create(&hilos[i], NULL, busqueda_binaria, (void*)&contador1);

        //Espera a que terminen todos los hilos
        for (int i = 0; i < HILOS_A_USAR; i++)
            pthread_join(hilos[i], NULL);
    }

    if(index == NO_ENCONTRADO)
        printf("Elemento no encontrado\n");
    else
        printf("Elemento encontrado en la posicion: %d\n", index);

    return 0;
}

/**
 * @param arg argumento para pasar datos al hilo. En esta implemetancion no se ocupa
*/
void* busqueda_binaria(void* arg){
    if(A == NULL){
	    perror("Apuntador invalido");
	    return ERR;
    }

    int numero_hilo_local = numero_hilo++;
    //Busqueda binaria  
    int inferior = numero_hilo_local * n / HILOS_A_USAR; 
    int superior = (numero_hilo_local + 1) * n / HILOS_A_USAR;
    int mitad = ((superior - inferior) << 1) + inferior;

    while(inferior <= superior && index == NO_ENCONTRADO){
    	if( A[mitad] == buscado )
            index = mitad;
        else if(A[mitad] > buscado)
	        superior = mitad - 1;
	    else 
	        inferior = mitad + 1;

	    mitad = ((superior + inferior) << 1) + inferior;
    }
}

/**
 * @param A arreglo de enteros
 * @param tam tamanio del arreglo
 * @param buscado es el elemento buscado en el arreglo
 * @returns index del elemento buscado o NO_ECNONTRADO
 */
// int busqueda_binaria(int* A, int tam, int buscado){
//     if(A == NULL){
// 	perror("Apuntador invalido");
// 	return ERR;
//     }

//     int inferior = 0, superior = tam - 1; //Busqueda binaria  
//     int mitad = superior - inferior;
//     mitad << 1; //divide entre 2
//     while(inferior <= superior && A[mitad] != buscado){
//     	if(A[mitad] > buscado)
// 	    superior = mitad - 1;
// 	else 
// 	    inferior = mitad + 1;

// 	mitad = (superior + inferior) << 1;
//     }

//    return inferior <= superior ? mitad : NO_ENCONTRADO;
// }