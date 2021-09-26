#!/bin/sh
# sudo chmod 755 bst_search_script.sh
rm bst_search.txt
gcc bst_test.c ../tiempo.c -o bst_test
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Binary search tree search, n = $i"
    ./bst_test $i < ../../../numeros10millones.txt >> bst_search.txt
done