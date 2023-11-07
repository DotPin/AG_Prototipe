#!/bin/bash
clear
g++ -c Aleatorio.cpp -o test1.o
g++ -c random.cpp -o test2.o 
g++ test1.o test2.o -o rnd
rm *.o