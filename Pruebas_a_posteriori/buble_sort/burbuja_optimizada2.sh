#!/bin/sh
# sudo chmod 755 burbuja_optimizada2.sh
#Borra el archivo anterior de mediciones
rm burbuja_optimizada2.txt
gcc burbuja_optimizada2.c ../tiempo.c -o bo2
for i in  20 40 60 80 100 200 400 600 800 1000 2000 4000 6000 8000 10000 20000 40000 60000 80000 100000
do
    echo "Burbuja optimizada 2 con n -> $i"
    ./bo2 $i < ../../../numeros10millones.txt >> burbuja_optimizada2.txt
done
