#include <iostream>
#include <random>
#include <time.h>

using namespace std;

//generacion de numeros aleatorios mediante una distribución matemática

int main()
{
    srand(time(NULL)); 
    const int nrolls=10000;  // number of experiments
    const int nstars=95;     // maximum number of stars to distribute
    const int nintervals=10; // number of intervals

    default_random_engine generator;
    uniform_real_distribution<float> distribution(0.0,1.0);

    int p[nintervals]={};

    for (int i=0; i<10; ++i) {
        cout<<"gen: "<<generator<<"\n";
        float number = distribution(generator);
        cout<<"num: "<<number<<"\n";
        ++p[int(nintervals*number)];
    }

    return 0;
}