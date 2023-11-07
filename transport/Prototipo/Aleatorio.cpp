#include <random>
#include "Aleatorio.h"

float Aleatorio::float_uniform(float a, float b){
    uniform_real_distribution<float> distribucion(a,b);

    return distribucion(generador);
}

int Aleatorio::int_uniform(int a, int b){
    uniform_int_distribution<int> distribucion(a,b);

    return distribucion(generador);
}