#!/bin/bash
# sudo chmod 777 fib.sh
gcc fib.c ../tiempo.c -o fib
./fib 3 < ../../../10millones.txt >> fib.txt
