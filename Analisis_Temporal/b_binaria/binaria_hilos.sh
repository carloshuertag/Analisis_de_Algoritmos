#!/bin/sh
# sudo chmod 755 binaria_hilos.sh
rm binaria_hilos.txt
gcc b_binaria_hilos.c ../tiempo.c -o bbh -lpthread
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Binaria_hilos con n = $i"
    ./bbh $i < numeros10millones.txt >> binaria_hilos.txt
done