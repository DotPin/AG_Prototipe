#ifndef ALEATORIO_H
#define ALEATORIO_H
#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

class Aleatorio
{
        int seed=0;
    default_random_engine generador;

    public:
        Aleatorio(int sdd);
        ~Aleatorio(){};
        float float_uniform(float a, float b);
        int int_uniform(int a, int b);
        int getSeed();
};

#endif
