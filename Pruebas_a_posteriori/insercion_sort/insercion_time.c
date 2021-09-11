#include <stdio.h>
#include <stdlib.h>

int* insercion(int* A, int n); //Función de ordenamiento tomndo como parametro 2 numeros de ordenmiento 

int main() {
	
	//scanf();
	int arreglo[] = {1,2,9,20,5,7,8};
	int* arrOrdenado;
	arrOrdenado = insercion(arreglo, 7);
	printf("Arreglo Ordendo: [ ");
	for (int i=0; i < sizeof(arrOrdenado)-1; i++){
		if(i == sizeof(arrOrdenado)-2)
			printf("%d ", arrOrdenado[i]);
		else
			printf("%d, ", arrOrdenado[i]);
	}
	printf("]\n");
	return 0;
}

int* insercion(int *A, int n){
	for(int i=0; i<sizeof(A)-1; i++){
		int j=i;
		int temp = A[i];
		while(j>0 && temp<A[j-1]){
			A[j] = A[j-1];
			j--;
		}
		A[j] = temp;	
	}
	return A;
}
