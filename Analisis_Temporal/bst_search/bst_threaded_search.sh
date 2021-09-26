#!/bin/sh
# sudo chmod 755 bst_threaded_search.sh
rm threaded_bst_search.txt
gcc -lpthread threaded_bst_test.c ../tiempo.c -o threaded_bst_test
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Threaded binary search tree search, n = $i"
    ./threaded_bst_test $i < ../../../numeros10millones.txt >> threaded_bst_search.txt
done