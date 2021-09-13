#!/bin/sh
# sudo chmod 755 seleccion_test.sh

gcc seleccion_time.c ../tiempo.c -o seleccion
for i in  100 1000 5000 10000 50000 100000 200000 400000 500000 600000 800000 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Insercion con n -> $i"
    echo .::tiempo con n = $i >> insercion_test.txt
    ./seleccion $i < ../../../numeros10millones.txt >> insercion_test.txt
done
