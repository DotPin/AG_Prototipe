#!/bin/bash
clear
g++ -c prueba.cpp -o test1.o
g++ -c obtengo.cpp -o test2.o 
g++ test1.o test2.o -o run
rm *.o