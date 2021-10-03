#!/bin/sh
# sudo chmod 755 exponencial_wc.sh
rm exponencial_wctime.txt

gcc expBusqueda_wctime.c ../tiempo.c -o exponencial_wc

for n in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
        echo "Busqueda exponencial con n = $n"
        ./exponencial_wc $n < ../../../10millones.txt >> exponencial_wctime.txt
done