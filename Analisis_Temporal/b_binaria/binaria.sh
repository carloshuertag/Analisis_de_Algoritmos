#!/bin/sh
# sudo chmod 755 binaria.sh
rm binaria.txt
gcc b_binaria.c ../tiempo.c -o bb
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Binaria con n = $i"
    ./bb $i < numeros10millones.txt >> binaria.txt
done