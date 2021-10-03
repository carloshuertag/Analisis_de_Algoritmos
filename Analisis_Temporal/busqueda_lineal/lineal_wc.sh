#!/bin/sh
# sudo chmod 755 lineal_wc.sh
rm lineal_wc.txt
gcc b_lineal_wc.c ../tiempo.c -o blwc
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Lineal con n = $i"
    ./blwc $i < ../../../10millones.txt >> lineal_wc.txt
done