#!/bin/bash
clear
g++ -c prueba.cpp -o test1.o
g++ -c Aleatorio.cpp -o test2.o
g++ -c shuffle.cpp -o test3.o
g++ test1.o test2.o test3.o -o shf
rm *.o