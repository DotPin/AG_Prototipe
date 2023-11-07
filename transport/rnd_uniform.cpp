#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Aleatorio.h"
#include <time.h>

using namespace std;

//generación de numeros aleatorios con el uso de semilla

int main(int argc, char *argv[]){

    int seed;
    
    if (stoi(argv[3])!= 0){
        cout<<"Salida Aleatoria con semilla: \n";
        //srand(stoi(argv[3]));
        seed = stoi(argv[3]);
    }else{
        cout<<"Salida Aleatoria sin semilla: \n";
        //srand(time(NULL)); 
        seed = time(NULL);
    }
    
    Aleatorio *rnd = new Aleatorio(seed);
 
    cout<<"Valores Flotantes\n";
    for (size_t i = 0; i < 10; i++){
        cout<<rnd->float_uniform(stof(argv[1]),stof(argv[2]))<<"\n";
    }
    cout<<"\n";

    cout<<"Valores Enteros\n";
    for (size_t i = 0; i < 10; i++){
        cout<<rnd->int_uniform(stof(argv[1]),stof(argv[2]))<<"\n";
    }

    delete rnd;
    return 0;
}