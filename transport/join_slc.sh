#!/bin/bash
clear
g++ -c Aleatorio.cpp -o test1.o -O0 -g
g++ -c prueba.cpp -o test2.o -O0 -g
g++ -c selector.cpp -o test3.o -O0 -g
g++ -o sllc -std=c11 -Wall -ggdb3 test1.o test2.o test3.o
rm *.o