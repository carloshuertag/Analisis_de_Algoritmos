#!/bin/bash
# sudo chmod 777 merge_sort.sh
gcc merge_sort.c ../tiempo.c -o merge_sort
./merge_sort 500000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 100 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 1000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 5000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 10000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 50000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 100000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 200000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 400000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 600000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 800000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 1000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 2000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 3000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 4000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 5000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 6000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 7000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 8000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 9000000 < ../../../numeros10millones.txt >> merge_sort.txt
./merge_sort 10000000 < ../../../numeros10millones.txt >> merge_sort.txt