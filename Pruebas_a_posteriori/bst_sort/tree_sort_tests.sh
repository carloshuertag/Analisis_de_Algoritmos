#!/bin/bash
# sudo chmod 777 tree_sort_tests.sh
gcc bst_test.c ../tiempo.c -o bst_test
./bst_test 500000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 100 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 1000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 5000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 10000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 50000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 100000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 200000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 400000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 600000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 800000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 1000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 2000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 3000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 4000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 5000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 6000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 7000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 8000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 9000000 < ../numeros10millones.txt >> tree_sort_test.txt
./bst_test 10000000 < ../numeros10millones.txt >> tree_sort_test.txt