#!/bin/bash
# sudo chmod 777 fib.sh
gcc fib.c ../tiempo.c -o fib -lpthread
./fib 3 < ../../../numeros10millones.txt >> fib.txt
