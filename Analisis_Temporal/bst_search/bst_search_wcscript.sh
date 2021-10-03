#!/bin/sh
# sudo chmod 755 bst_search_script.sh
rm bst_search_wc.txt
gcc bst_wctest.c ../tiempo.c -o bst_wctest
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Binary search tree search, n = $i"
    ./bst_wctest $i < ../../../10millones.txt >> bst_search_wc.txt
done