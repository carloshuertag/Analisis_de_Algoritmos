#!/bin/bash
# sudo chmod 777 fib.sh
rm fib.txt
gcc fib.c ../tiempo.c -o fib
for i in  1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000
do
    echo "Fibonacci search, n = $i"
    ./fib $i < ../../../10millones.txt >> fib.txt
done