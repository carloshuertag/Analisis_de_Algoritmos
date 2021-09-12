#!/bin/sh
# sudo chmod 755 burbuja_simple.sh
#Borra el archivo anterior de mediciones
rm burbuja_simple.txt
gcc burbuja_simple.c ../tiempo.c -o bs
for i in  100 1000 5000 10000 50000 100000 200000 400000 500000 600000 800000 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    #../bs $i < ../numeros10millones.txt >> burbuja_simple.txt
    echo "Burbuja simple con n -> $i"
    ./bs $i < Numeros/numeros10millones.txt >> burbuja_simple.txt
done