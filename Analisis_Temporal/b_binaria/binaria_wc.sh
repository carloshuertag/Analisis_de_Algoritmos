#!/bin/sh
# sudo chmod 755 binaria_wc.sh
rm binaria_wc.txt
gcc b_binaria_wc.c ../tiempo.c -o bbwc
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Binaria con n = $i"
    ./bbwc $i < ../../../10millones.txt >> binaria_wc.txt
done
