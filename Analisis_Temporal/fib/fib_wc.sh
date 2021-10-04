#!/bin/sh
# sudo chmod 777 fib_wc.sh
rm fib_wc.txt
gcc fib_wc.c ../tiempo.c -o fib_wc
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Fibonacci search, n = $i"
    ./fib_wc $i < ../../../10millones.txt >> fib_wc.txt
done
