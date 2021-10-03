/**
 *  @author @Reina Beatriz Juarez Leonel
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  @version 1.0
 *  ESCOM-IPN
 *  Medición de tiempo de la busqueda exponencial de un numero x dentro de un arreglo ordenado de tamaño n, ocupando hilos en C.
 *  Compilación: gcc expHilosFix_time.c ../tiempo.c -o exponencialHilos_time -lpthread
 *  Ejecución: ./exponencialHilos_time n < ../../../10millones.txt
*/

//LIBRERIAS
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"
#include <math.h>

//DEFINICIONES 
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define NumThreads 4
#define N_Veces 20

//DECLARACIÓN DE FUNCIONES
int busquedaBinaria(int arr[], int l, int r, int x);
int busquedaExponencial(int arr[], int n, int x);
void* exponencial(void* args);

//DECLARACION DE ESTRUCTURAS
struct args {
    int *A;
    int n;
    int x;
    int li;
    int id;
};

//PROGRAMA PRINCIPAL
int main (int argc, char* argv[]){
    //Declaracion de variables del main
    int n; //n determina el tamaño del algoritmo dado por argumento al ejecutar
    int x; //x numero a buscar dado por el argumento
    int i; //Variables para loops
    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0; //para los tiempos
    int numBuscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644,
                        1295390003, 450057883,  18765041, 1980098116, 152503, 5000,
                        1493283650, 214826, 1843349527, 1360839354, 2109248666,
                        2147470852, 0};

    /*Recepción y decodificación de argumentos*/
    if(argc!=2){ //Si no se introducen exactamente 4 argumentos (Cadena de ejecución, tamañoArreglo=n, numero a buscar x y numero de hilos)
        printf("\nIndique el tamaño del arreglo y el numero a buscar - Ejemplo: %s 100\n",argv[0]);
        exit(1);
    } 

    //Tomar el segundo argumento como tamaño del algoritmo y el tercero como numero a buscar
    else{
        n = atoi(argv[1]);
    }

    int *A = (int*)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
    
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
        x = numBuscar[j];

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

            if (pthread_create (&thread[i], NULL, exponencial,(void*)datos) != 0 ){
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
    printf("\nBusqueda exponencial_hilos con n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(A);
    exit(0);
   return 0;
}

void* exponencial(void* dato){
    struct args *datos = dato;
    busquedaExponencial(datos->A, datos->n, datos->x);
    pthread_exit(NULL);
}


/**
 *  Busca un numero x en un arreglo de tamaño n usando el algoritmo de busqueda exponencial
 *  @param arr arreglo de tamaño n
 *  @param n tamaño del arreglo
 *  @param x numero a buscar
 *  @return la posicion de la primera ocurrencia de x en el arreglo
*/
int busquedaExponencial(int arr[], int n, int x){
    if (arr[0] == x) // Si x esta en la primer posicion del arreglo
        return 0;
 
    // Encontrando un rango para la busqueda binaria mediante duplicacion repetida
    int i = 1;
    while (i < n && arr[i] <= x)
        i = i*2;
 
    //  Llamando la busqueda binaria para el rango encontrado
    return busquedaBinaria(arr, i/2, min(i, n-1), x);
}

/**
 *  Busca un numero x en un arreglo de tamaño n usando el algoritmo de busqueda binaria iterativa
 *  @param arr arreglo de tamaño n
 *  @param l limite del subarreglo izquierdo
 *  @param r limite del subarreglo derecho
 *  @param x numero a buscar
 *  @return la posicion de x en el arreglo si se encuentra, de lo contarario -1.
*/
int busquedaBinaria(int arr[], int l, int r, int x){
    while (l <= r) {
        int m = l + (r - l) / 2;
  
        if (arr[m] == x)//Checa si x esta a la mitad
            return m;
  
        if (arr[m] < x) // Si x es mas grande, ignora la mitad izquierda
            l = m + 1;
  
        else // Si x es mas pequeña, ignora la mitad derecha
            r = m - 1;
    }
    return -1; //Si no encuentra el numero
}

