#ifndef ALEATORIO_H
#define ALEATORIO_H
#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

class Aleatorio
{
    default_random_engine generador;

    public:
        Aleatorio(int sdd){ generador.seed(sdd); };
        ~Aleatorio(){};
        float float_uniform(float a, float b);
        int int_uniform(int a, int b);
};

#endif
