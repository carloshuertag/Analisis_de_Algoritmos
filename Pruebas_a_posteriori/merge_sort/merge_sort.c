#include <stdio.h>
#include <stdlib.h>

int i, j, k, n, p, q, r;

void mergeSort(int* A, int p, int r);
void merge(int* A, int p, int q, int r);

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

    mergeSort(A, 0, n-1);

    printf("\nOrdenados:");
    for(int i = 0; i < n; i++)
        {
            printf("%d ", A[i]);
        }
    
}

void mergeSort(int* A, int p, int r)
{
    if(p < r)
    {
        q = ((p+r)/2);
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    }
}


void merge(int* A, int p, int q, int r)
{
    int* C;
    int l=r-p+1;
    i=p;
    j=q+1;
    for (size_t k = 0; k >=1; k++)
    {
        if (i<=q && j<=r)
        {
            if (A[i]<A[j])
            {
                C[k]=A[i];
                i++;
            }
        else if (i<=q)
        {
            C[k]=A[i];
        i++;
        }
        else
        {
            C[k]=A[j];
            j++;
        }
        }
    A[p-r] = C[k];
    }
}