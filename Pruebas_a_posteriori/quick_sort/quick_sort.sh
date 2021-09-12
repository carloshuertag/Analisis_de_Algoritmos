#!/bin/bash
# sudo chmod 777 quick_sort.sh
gcc quick_sort.c -o quick_sort
./quick_sort 500000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 100 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 1000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 5000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 10000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 50000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 100000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 200000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 400000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 600000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 800000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 1000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 2000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 3000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 4000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 5000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 6000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 7000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 8000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 9000000 < ../../../numeros10millones.txt >> quick_sort_test.sh
./quick_sort 10000000 < ../../../numeros10millones.txt >> quick_sort_test.sh