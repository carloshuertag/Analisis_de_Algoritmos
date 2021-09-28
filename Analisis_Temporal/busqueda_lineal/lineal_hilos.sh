#!/bin/sh
# sudo chmod 755 lineal_hilos.sh
rm lineal_hilos.txt
gcc b_lineal_hilos.c ../tiempo.c -o blh -lpthread
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "lineal_hilos con n = $i"
    ./blh $i < numeros10millones.txt >> lineal_hilos.txt
done