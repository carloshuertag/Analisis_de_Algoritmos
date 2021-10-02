#!/bin/sh
# sudo chmod 755 lineal.sh
rm lineal.txt
gcc b_lineal.c ../tiempo.c -o bl
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Lineal con n = $i"
    ./bl $i < ../../../numeros10millones.txt >> lineal.txt
done
