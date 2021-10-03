/**
 *  @author @Reina Beatriz Juarez Leonel
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  @version 1.0
 *  ESCOM-IPN
 *  Busqueda de un numero 2147483528 dentro de un arreglo ordenado de tamaño n, ocupando la busqueda exponencial en C.
 *  Compilación: gcc expBusqueda_wctime.c ../tiempo.c -o exponencial_wc
 *  Ejecución: ./exponencial_wc n < ../../../10millones.txt
*/

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include "../tiempo.h"

//DEFINICIONES
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

//DECLARACIÓN DE FUNCIONES
int busquedaBinaria(int arr[], int l, int r, int x);
int busquedaExponencial(int arr[], int n, int x);

//PROGRAMA PRINCIPAL
int main(int argc, char *argv[])
{
    //Declaracion de variables del main
    int n;                                                          //n determina el tamaño del algoritmo dado por argumento al ejecutar
    int i;                                                          //Variables para loops
    double utime0, stime0, wtime0, utime1, stime1, wtime1, avg = 0; //para los tiempos
    int numBuscar = 2147483528;
    /*Recepción y decodificación de argumentos*/
    if (argc != 2)
    { //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y tamañoArreglo=n)
        printf("\nIndique el tamaño del arreglo y el numero a buscar - Ejemplo: %s 100\n", argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del algoritmo y el tercero como numero a buscar
    else
        n = atoi(argv[1]);
    int *A = (int *)malloc(n * sizeof(int)); // tamaño de memoria para el arreglo
    if (A == NULL)
    {
        perror("Espacio de memoria no asignado\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);             // llenando el arreglo
    uswtime(&utime0, &stime0, &wtime0); // empieza la medición de tiempos
    busquedaExponencial(A, n, numBuscar);
    //int res = busquedaExponencial(A, n, x);
    //(res == -1)? printf("El elemento no se encuentra en el arreglo\n")
    //             : printf("El elemento se encuentra en el indice %d\n", res);
    uswtime(&utime1, &stime1, &wtime1); // termina la medición de tiempos
    avg += wtime1 - wtime0;             // acumular el tiempo real
    printf("\nBusqueda exponencial con n = %d\nPromedio del tiempo real: %.10e s\n", n, avg);
    free(A);
    exit(0);
    return 0;
}

/**
 *  Busca un numero x en un arreglo de tamaño n usando el algoritmo de busqueda exponencial
 *  @param arr arreglo de tamaño n
 *  @param n tamaño del arreglo
 *  @param x numero a buscar
 *  @return la posicion de la primera ocurrencia de x en el arreglo
*/
int busquedaExponencial(int arr[], int n, int x)
{
    if (arr[0] == x) // Si x esta en la primer posicion del arreglo
        return 0;

    // Encontrando un rango para la busqueda binaria mediante duplicacion repetida
    int i = 1;
    while (i < n && arr[i] <= x)
        i = i * 2;

    //  Llamando la busqueda binaria para el rango encontrado
    return busquedaBinaria(arr, i / 2, min(i, n - 1), x);
}

/**
 *  Busca un numero x en un arreglo de tamaño n usando el algoritmo de busqueda binaria iterativa
 *  @param arr arreglo de tamaño n
 *  @param l limite del subarreglo izquierdo
 *  @param r limite del subarreglo derecho
 *  @param x numero a buscar
 *  @return la posicion de x en el arreglo si se encuentra, de lo contarario -1.
*/
int busquedaBinaria(int arr[], int l, int r, int x)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2;

        if (arr[m] == x) //Checa si x esta a la mitad
            return m;

        if (arr[m] < x) // Si x es mas grande, ignora la mitad izquierda
            l = m + 1;

        else // Si x es mas pequeña, ignora la mitad derecha
            r = m - 1;
    }
    return -1; //Si no encuentra el numero
}
