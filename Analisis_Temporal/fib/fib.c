/**
 *  Programa de prueba para la búsqueda por árbol (iterativa)
 *  @author @huerta2502 Carlos Huerta García
 *  @copyright Septiembre 2021
 *  @version 1.0
 *  Compilación: gcc bst_test.c ../tiempo.c -o bst_test
 *  Ejecución: ./bst_test n < ../../../numeros10millones.txt
*/

#include <stdio.h>

int i;

int fib(int n);

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n-1)+fib(n-2);
}

int main(int argc, char *argv[])
{
    int n, item;
    if (argc != 3)
    {
        fprintf(stderr, "\nPlease enter the array length, e.g.: %s 10000 123456\n",
                argv[0]);
        exit(1);
    }
    else
    {
        n = atoi(argv[1]); // Toma del argumento la longitud del arreglo
        item = atoi(argv[2]); // item to search on array
    }
    int *arr = (int *)malloc(n * sizeof(int)); // asigna la memoria para el arreglo
    if (arr == NULL)
    {
        perror("Memory not allocated.\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]); // guarda los elemetos introducidos en el arreglo

}


#include <stdio.h>
 
// Utility function to find minimum of two elements
int min(int x, int y) { return (x <= y) ? x : y; }
 
/* Returns index of x if present,  else returns -1 */
int fibMonaccianSearch(int arr[], int x, int n)
{
    /* Initialize fibonacci numbers */
    int fibMMm2 = 0; // (m-2)'th Fibonacci No.
    int fibMMm1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci
 
    /* fibM is going to store the smallest Fibonacci
       Number greater than or equal to n */
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
 
    // Marks the eliminated range from front
    int offset = -1;
 
    /* while there are elements to be inspected. Note that
       we compare arr[fibMm2] with x. When fibM becomes 1,
       fibMm2 becomes 0 */
    while (fibM > 1) {
        // Check if fibMm2 is a valid location
        int i = min(offset + fibMMm2, n - 1);
 
        /* If x is greater than the value at index fibMm2,
           cut the subarray array from offset to i */
        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
 
        /* If x is greater than the value at index fibMm2,
           cut the subarray after i+1  */
        else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
 
        /* element found. return index */
        else
            return i;
    }
 
    /* comparing the last element with x */
    if (fibMMm1 && arr[offset + 1] == x)
        return offset + 1;
 
    /*element not found. return -1 */
    return -1;
}
 
/* driver function */
int main(void)
{
    int arr[]
        = { 10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100,235};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 235;
      int ind = fibMonaccianSearch(arr, x, n);
  if(ind>=0)
    printf("Found at index: %d",ind);
  else
    printf("%d isn't present in the array",x);
    return 0;
}