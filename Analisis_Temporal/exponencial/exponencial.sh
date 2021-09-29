#!/bin/sh
# sudo chmod 755 exponencial.sh
rm exponencial_time.txt

gcc expBusqueda_time.c ../tiempo.c -o exponencial

for n in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
        echo "Busqueda exponencial con n = $n"
        ./exponencial $n < ../../../10millones.txt >> exponencial_time.txt
done