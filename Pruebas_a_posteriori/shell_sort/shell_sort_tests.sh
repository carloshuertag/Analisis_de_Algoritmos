#!/bin/bash
# sudo chmod 777 shell_sort_tests.sh
gcc shell_sort_test.c ../tiempo.c -o shell_sort_test
./shell_sort_test 500000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 100 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 1000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 5000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 10000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 50000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 100000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 200000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 400000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 600000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 800000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 1000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 2000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 3000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 4000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 5000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 6000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 7000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 8000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 9000000 < ../../../numeros10millones.txt >> shell_sort_test.txt
./shell_sort_test 10000000 < ../../../numeros10millones.txt >> shell_sort_test.txt