#!/bin/sh
# sudo chmod 755 insercion_test.sh

gcc insercion_time.c ../tiempo.c -o insercion
for i in  20 40 60 80 100 200 400 600 800 1000 2000 4000 6000 8000 10000 20000 40000 60000 80000 100000
do
    echo "Insercion con n -> $i"
    echo .::tiempo con n = $i >> insercion_test.txt
    ./insercion $i < ../../../numeros10millones.txt >> insercion_test.txt
done
