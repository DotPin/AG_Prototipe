#!/bin/bash

clear
g++ -c Aleatorio.cpp -o test1.o -O0 -g
g++ -c rnd_uniform.cpp -o test2.o -O0 -g
g++ -o rnd_uni -std=c11 -Wall -ggdb3 test1.o test2.o
rm *.o