#include <stdio.h>
#include <stdlib.h>

int i, j, n;

void quickSort(int* arr, int l, int h);
int pivote(int* A, int p, int r);
void intercambiar(int* A, int i, int j);

int main (int argc, char* argv[]){
    n=atoi(argv[1]);
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        	scanf("%d", &arr[i]);
    
    printf("Sin ordenar:");
    for(int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }

    quickSort(arr, 0, n-1);

    printf("\nOrdenados:");
    for(int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
}

void quickSort(int* arr, int l, int h)
{
    if (l<h)
    {
        int pi=pivote(arr, l, h);
        quickSort(arr, l, pi-1);
        quickSort(arr, pi+1, h);
    }
}

int pivote(int* arr, int l, int h)
{
    int piv=arr[h];
    i=l-1;
    j=l;

    //
    for (j = l; j <= h-1; j++)
    {
        if (arr[j] < piv)
        {
            i++;
            intercambiar(arr, i, j);
        }
    }
    intercambiar(arr, i+1, h);
    return (i + 1);
    //
}

void intercambiar(int* arr, int i, int j)
{
    int temp=arr[j];
    arr[j]=arr[i];
    arr[i]=temp;
}