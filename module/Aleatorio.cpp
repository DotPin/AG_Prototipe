#include <stdlib.h>     /* srand, rand */
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include "Aleatorio.h"

int aleatorio(int sm){      // rango del aleatoreo será [1,sm]
    return (1+rand())%(sm-1);
}


float Aleatorio::random(float a, float b){
     //usar propuesta de generacion de numeros aleatorios en 
    //Canavos George - Probabilidad Y Estadistica Aplicaciones Y Metodos, seccion 5.9.4, con 5.9.1

    float semilla = 12345;
    float intervalo=((b-a)/semilla);             // aleatoreao funciona con a=intervalo inicial, b=intervalo final
    float *vct = new float[12345];
    vct[0]=a;
    for(int i=1;i<semilla;i++){
        vct[i] = vct[i-1]+ intervalo; 
    }
    intervalo = vct[aleatorio(semilla)];
    delete vct;
    return intervalo;
}
