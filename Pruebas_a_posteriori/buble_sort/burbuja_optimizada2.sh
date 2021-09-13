#!/bin/sh
# sudo chmod 755 burbuja_optimizada2.sh
#Borra el archivo anterior de mediciones
rm burbuja_optimizada2.txt
gcc burbuja_optimizada2.c ../tiempo.c -o bo2
for i in  100 1000 5000 10000 50000 100000 200000 400000 500000 600000 800000 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Burbuja optimizada 2 con n -> $i"
    ./bo2 $i < ../../../numeros10millones.txt >> burbuja_optimizada2.txt
done
