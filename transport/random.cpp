#include <iostream>
#include "Aleatorio.h"

//genera numeros aleatorios 10 veces
//Permite ingreso de parámetros sin interacción por terminal, con posibilidad de uso de semilla
//~ new Aleatorio(seed) -> seed tipo Integer
// ej: ~./rnd {entero inferior} {entero superior} {flotante inferior} {flotante superior} {seed}
// ej: ~./rnd 23 90 0.23 1.12 15
int main(int argc, char *argv[]){

    int seed;

    if(atoi(argv[5])==0) seed = time(NULL);
    else seed = atoi(argv[5]);

    Aleatorio *rnd = new Aleatorio(seed);

    for(int i=0;i<10;i++){

        cout<<"\nSalida 1 Entera: "<<rnd->int_uniform(atoi(argv[1]),atoi(argv[2]));
        cout<<"\nSalida 2 Flotante: "<<rnd->float_uniform(stoi(argv[3]),stoi(argv[4]));
    }

    return 0;
}

