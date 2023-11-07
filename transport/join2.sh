#!/bin/bash
clear
g++ -c Aleatorio.cpp -o test1.o
g++ -c prueba.cpp -o test2.o
g++ -c trns3.cpp -o test3.o
g++ test1.o test2.o test3.o -o trn
rm *.o