#!/bin/sh
# sudo chmod 755 bst_search_script.sh
rm bst_search_wc.txt
gcc bst_wctest.c ../tiempo.c -o bst_wctest
for i in  10000 20000 30000 40000 50000 60000 70000 80000 90000 100000
do
    echo "Binary search tree search, n = $i"
    ./bst_wctest $i < ../../../10millones.txt >> bst_search_wc.txt
done