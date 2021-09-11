#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR 0

//Usadas en burbuja optimizada 2
#define SI 1
#define NO 0


void BurbujaSimple(int** A, int n);
void BurbujaOptimizada1(int** A, int n);
void BurbujaOptimizada2(int** A, int n);

int main() {
    int n;

    scanf("%d", n);
    
    int* A = (int*)malloc(sizeof(int) * n);
    if(A == NULL) return ERR;

    //TODO
    // Obtener los datos usando el archivo de 5000 números
    // Utilizar el código de medición

    return OK;
}

/* 
 * Ordena un arreglo usando burbuja simple
 * @param A doble apuntador a entero. Arreglo a ordenar.
 * @param n tamaño del arreglo
 */
int BurbujaSimple(int** A, int n) {
    if(A == NULL || *A == NULL) return ERR;

    int aux;
    for (int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - 1; j++)
            if( *A[j] > *A[j + 1] ){
                aux = *A[j];
                *A[j] = *A[j + 1];
                *A[j + 1] = aux;
            }
        
    
    for (int i = 0; i < n; i++) {
        printf("%d ", *A[i]);
    }

    return OK;
}

/* 
 * Ordena un arreglo usando burbuja optimizada 1
 * @param A doble apuntador a entero. Arreglo a ordenar.
 * @param n tamaño del arreglo
 */
int BurbujaOptimizada1(int** A, int n) {
    if(A == NULL || *A == NULL) return ERR;

    int aux;
    for (int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - 1 - i; j++)
            if( *A[j] > *A[j + 1] ){
                aux = *A[j];
                *A[j] = *A[j + 1];
                *A[j + 1] = aux;
            }
        
    
    for (int i = 0; i < n; i++) {
        printf("%d ", *A[i]);
    }

    return OK;
}

/* 
 * Ordena un arreglo usando burbuja optimizada 2
 * @param A doble apuntador a entero. Arreglo a ordenar.
 * @param n tamaño del arreglo
 */
int BurbujaOptimizada2(int** A, int n) {
    if(A == NULL || *A == NULL) return ERR;

    int aux;
    int i = 0;
    int cambios = SI; // true
    
    while( i < n - 1 && cambios != NO ) {
        cambios = NO;
        for(int j = 0; j < n - 1 - i; j++)
            if( *A[j] > *A[j + 1] ){
                aux = *A[j];
                *A[j] = *A[j + 1];
                *A[j + 1] = aux;
            }
        
        i++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", *A[i]);
    }

    return OK;
}