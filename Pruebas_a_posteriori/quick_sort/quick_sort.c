#include <stdio.h>
#include <stdlib.h>

int i, j, n, p, r;

void quickSort(int* A, int p, int r);
int pivote(int* A, int p, int r);
void intercambiar(int* A, int i, int j);

int main (int argc, char* argv[]){
    n=atoi(argv[1]);
    int *A = (int*)malloc(n * sizeof(int));
    int *C = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        	scanf("%d", &A[i]);
    
    printf("Sin ordenar:");
    for(int i = 0; i < n; i++)
        {
            printf("%d ", A[i]);
        }

    quickSort(A, 0, n-1);

    printf("\nOrdenados:");
    for(int i = 0; i < n; i++)
        {
            printf("%d ", A[i]);
        }
}

void quickSort(int* A, int p, int r)
{
    if (p<r)
    {
        j=pivote(A, p, r);
        quickSort(A, p, j-1);
        quickSort(A, j+1, r);
    }
}

int pivote(int* A, int p, int r)
{
    int piv=A[p];
    i=p+1;
    j=r;
    while (A[i]<piv && i<r)
    {
        i++;
        while (A[j]>piv)
        {
            j--;
        }
        if (i<j)
        {
            intercambiar(A, i, j);
        }
        else
        {
            intercambiar(A, p, j);
            
        }
    }
    return (j);
}

void intercambiar(int* A, int i, int j)
{
    int temp=A[j];
    A[j]=A[i];
    A[i]=temp;
}