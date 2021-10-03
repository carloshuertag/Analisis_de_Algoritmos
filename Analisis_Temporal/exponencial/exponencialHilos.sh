#!/bin/sh
# sudo chmod 755 exponencialHilos.sh
rm exponencialHilos_time.txt

gcc expHilosFix_time.c ../tiempo.c -o exponencialHilos_time -lpthread

for n in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
        echo "Busqueda exponencial_hilos con n = $n"
        ./exponencialHilos_time $n < ../../../10millones.txt >> exponencialHilos_time.txt
done