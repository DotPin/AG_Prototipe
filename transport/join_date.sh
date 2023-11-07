#!/bin/bash
clear
g++ -c date.cpp -o test1.o -O0 -g
g++ -c Aleatorio.cpp -o test2.o -O0 -g
g++ -c prueba.cpp -o test3.o -O0 -g
g++ -o date -std=c11 -Wall -ggdb3 test1.o test2.o test3.o
rm *.o
