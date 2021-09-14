#!/bin/sh
# sudo chmod 755 burbuja_simple.sh
#Borra el archivo anterior de mediciones
rm burbuja_simple.txt
gcc burbuja_simple.c ../tiempo.c -o bs
for i in  20 40 60 80 100 200 400 600 800 1000 2000 4000 6000 8000 10000 20000 40000 60000 80000 100000
do
    echo "Burbuja simple con n -> $i"
    ./bs $i < ../../../numeros10millones.txt >> burbuja_simple.txt
done