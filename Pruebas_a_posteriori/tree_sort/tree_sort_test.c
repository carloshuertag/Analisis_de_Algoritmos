/**
 *  binary search tree tree sort test program.
 *  @author @huerta2502
 *  compile: gcc tree_sort_test.c ../tiempo.c -o tree_sort_test
 *  execute: ./tree_sort_test n < ../numeros10millones.txt
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst_entry.h"
#include "bst.h"
#include "tree_sort.h"
#include "../tiempo.h"


int main(int argc, char** argv)
{
    double utime0, stime0, wtime0,utime1, stime1, wtime1; 
	int n; // array length
	register unsigned int i; // iterator
    if (argc!=2) 
	{
		fprintf(stderr, "\nPlease enter the array length, e.g.: %s 1000\n",
                argv[0]);
		exit(1);
	} 
	else
		n=atoi(argv[1]); //get array size from arguments
    int *arr = (int*)malloc(n * sizeof(int)); // allocate memory for array
    if (arr == NULL) {
        perror("Memory not allocated.\n");
        exit(1);
    }
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]); // store array with given elements
    uswtime(&utime0, &stime0, &wtime0); // start timer
    treeSort(arr, n);
    uswtime(&utime1, &stime1, &wtime1); // check timer
	printf("\nreal (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",
            utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",
            100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
    exit(0);
}