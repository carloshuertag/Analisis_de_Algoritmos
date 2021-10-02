/**
 *  @author @Angel Alan Hernandez Dominguez
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  ESCOM-IPN
 *  Medición tiempo de busqueda binaria
 *  Compilación: gcc b_binaria.c tiempo.c -o bb
 *  Ejecución: ./bbh 100000 < 10millones.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"

#define OK 1
#define ERR -1
#define NO_ENCONTRADO -2

int busqueda_binaria(int* A, int tam, int buscado);

int main(int argc, char* argv[]) {
    int n;
    int* A;
    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0; //para los tiempos
    int buscados[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644,
                    1295390003, 450057883,  18765041, 1980098116, 152503, 5000,
                    1493283650, 214826, 1843349527, 1360839354, 2109248666,
                    2147470852, 0};
    
    int a[] = {
        197,236,485,857,902,1031,1124,1134,1179,1540,1630,1891
    };
    
    //Recepción y decodificación de argumentos
    if (argc!=2){ //Se espera el valor n
		printf("\nIngrese el tamanio del arreglo: \n");
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
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for(int i = 0; i < 20; i++){
        uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
        int index = busqueda_binaria(A, n, buscados[i]); //Busca el elemento
        uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
        avg += wtime1 - wtime0; // acumular el tiempo real
        stime0 = stime1 = utime0 = utime1 = wtime0 = wtime1 = 0.0; // reiniciar
        // printf("%d ", buscados[i]);
        // if(index == NO_ENCONTRADO)
        //     printf("Elemento no encontrado\n");
        // else
        //     printf("Elemento encontrado en la posicion: %d\n", index);
    }
    avg /= 20; // promediar el tiempo real
    printf("\nBinaria con n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(A);

    return 0;
}


/**
 * @param A arreglo de enteros
 * @param tam tamanio del arreglo
 * @param buscado es el elemento buscado en el arreglo
 * @returns index del elemento buscado o NO_ENCONTRADO
 */
int busqueda_binaria(int* A, int tam, int buscado){
    if(A == NULL){
        perror("Apuntador invalido");
        return ERR;
    }

    int inferior = 0, superior = tam - 1; //Busqueda binaria  
    int mitad = ((superior - inferior) >> 1) + inferior;
    int index = NO_ENCONTRADO; //Index del elemento buscado
    while(inferior <= superior && index == NO_ENCONTRADO){
        if(A[mitad] == buscado)
            index = mitad;
        else if(A[mitad] > buscado)
            superior = mitad - 1;
        else 
            inferior = mitad + 1;

        mitad = ((superior - inferior) >> 1) + inferior;
    }

   return index;
}