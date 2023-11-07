#!/bin/bash
clear
g++ -c binary.cpp -o test1.o
g++ test1.o -o bin
rm *.o