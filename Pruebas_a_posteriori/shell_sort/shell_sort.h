/**
 *  Ordena un arreglo de tamaño n por el algoritmo shell.
 *  @param arr el arreglo a ordenar.
 *  @param n el tamaño del arreglo.
*/
void shellSort(int* arr, int n){
    register int k, b, i, temp;
    for(k = n/2; k >= 1; k/=2){ // empieza el ciclo con un hueco de n/2, que luego disminuye
        b = 1;
        while(b != 0){ // hasta que se encuentre el lugar de arr[i] en los elementos ordenados del hueco
            b = 0; // bandera
            for(i = k; i <= n - 1; i++){ // ordenamiento por incersión para el tamaño del hueco
                if(arr[i - k] > arr[i]){
                    temp = arr[i];  // añade un elemento a los ordenados en el hueco
                    arr[i] = arr[i - k]; // mueve hacia la posición anterior los elementos
                    arr[i - k] = temp; // coloca en su lugar al elemento original
                    b++;
                }
            }
        }
    }
}
/**
 *  better implementation of shell sort without flags and less assignments
 *  sorts a given array of given length.
 *  @param arr array to sort.
 *  @param n array length.
*/
void shellSort1(int* arr, int n){
    register unsigned int gap, i, j, temp;
    for(gap = n/2; gap > 0; gap/=2) // start loop with a n/2 gap, then reduce it
        for(i = gap; i < n; i++){// gapped insertion sort for the gap size
            temp = arr[i]; // add element to gap-sorted elements
            for(j = i; j >= gap && arr[j - gap] > temp; j-=gap) // until the location for arr[i] is found in gap-sorted elements
                arr[j] = arr[j - gap]; // shift gap-sorted elements up
            arr[j] = temp; // put the original element in its right location
        }
}