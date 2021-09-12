/**
 *  sorts a given array of given length.
 *  @param arr array to sort.
 *  @param n array length.
*/
void shellSort(int* arr, int n){
    register int k, b, i, temp;
    for(k = n/2; k >= 1; k/=2){ // start loop with a n/2 gap, then reduce it
        b = 1;
        while(b != 0){ // until the location for arr[i] is found in gap-sorted elements
            b = 0; // flag
            for(i = k; i <= n - 1; i++){ // gapped insertion sort for the gap size
                if(arr[i - k] > arr[i]){
                    temp = arr[i];  // add element to gap-sorted elements
                    arr[i] = arr[i - k]; // shift gap-sorted elements up
                    arr[i - k] = temp; // put the original element in its right location
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