/**
 *  @author @Reina Beatriz Juarez Leonel
 *  Curso: Análisis de algoritmos
 *  (C) Septiembre 2021
 *  @version 1.0
 *  ESCOM-IPN
 *  Busqueda de un numero x dentro de un arreglo ordenado de tamaño n, ocupando la busqueda exponencial en C.
 *  Compilación: "gcc exponencialBusqueda.c -o exponencial"
 *  Ejecución: "exponencial n x <../../../10millones.txt"
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;                          // TMAÑO DE LA SECUENCIA
int *arrfib;                    // ARREGLO PARA CADA VALOR
int i;                          

void *runn(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("el formato es:./fib <valor>\n");
        return -1; //ERROR
    }

    if (atoi(argv[1]) < 0)
    {
        printf("%d debe ser>0\n", atoi(argv[1]));
        return -1; //ERROR
    }

    n = atoi(argv[1]);
    arrfib = (int *)malloc(n * sizeof(int)); //TAMAÑO DEL ARREGLO
    pthread_t *threads = (pthread_t *) malloc(n * sizeof(pthread_t)); //TAMAÑO DEL ARREGLO DE HILOS
    pthread_attr_t attr; //ATRIBUTO DEL HILO

    pthread_attr_init(&attr);

    for (i=0; i<n; i++)
    {
        pthread_create(&threads[i], &attr, runn, NULL);
    }                           //CREACIÓN DE HILOS

    int j;

    for (j = 0; j < n; j++)
    {
        pthread_join(threads[j], NULL);
    }                           // End of wating the threads to exit.

    // printing arrfib.
    printf("The Fibonacci sequence.:");
    int k;

    for (k = 0; k < n; k++)
    {
        printf("%d,", arrfib[k]);
    }                           // End of printing arrfib.
    return 0;
}                               // End of main.

void *runn(void *arg)
{
    if (i == 0)
    {
        arrfib[i] = 0;
        pthread_exit(0);
    }                           // first fib term

    if (i == 1)
    {
        arrfib[i] = 1;
        pthread_exit(0);
    }                           // seconed fib term
    else
    {
        arrfib[i] = arrfib[i - 1] + arrfib[i - 2];
        // printf("arrfib[%d]%d,\n",i,arrfib[i]);
        pthread_exit(0);        // thread exit.
    }                           // End of else
}                               // End of run.