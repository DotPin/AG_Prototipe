#include "prueba.h"
#include <cstdlib>  
#include <stdlib.h>     /* srand, rand */
#include "Aleatorio.h"
#include <iostream>
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include <list>

using namespace std;

//Problema de selección mediante torneo, donde una cierta población ingresa, 
//por un proceso cíclico con total de la población, 
//se escojen aleatoriamente una porción de individuos, usando distribución por semilla,
//y se escoge el mejor dependiendo si se necesita un mínimo o máximo por grupo escogido.

//input y ejecución.
//sh join_slc.h
// ./sllc [semilla] [cant individios]

void mostrar(list<prueba> ing){

    list<prueba>::iterator it;
    cout<<"\nMuestra";
    for (it=ing.begin(); it!=ing.end(); it++){
        cout<<"\n"<<it->name<<"|"<<it->valor;
    }
}

list<prueba> agrupa(Aleatorio *rnd, list<prueba> padre){

    list<prueba> buff, group;
    list<prueba>::iterator it,it2;
    int len = round(padre.size()/5), rn;

    for (int g = 0; g < len; g++){
        it=padre.begin();
        advance(it, rnd->int_uniform(0,padre.size()-1));
        buff.splice(buff.end(),padre,it);
    }
    it2=buff.begin();
    for (it=buff.begin(); it!=buff.end(); it++){
        if(it2->valor > it->valor){
            it2=it;
        } 
    }
    group.splice(group.end(),buff,it2);

    return group;
}

list<prueba> seleciona(Aleatorio *rn, list<prueba> padre){
    
    list<prueba> aux, finish;
    list<prueba>::iterator it;
    int len= padre.size();

    for (size_t i = 0; i < len; i++){
        aux = agrupa(rn, padre);
        it = aux.begin();
        finish.splice(finish.end(),aux,it);
    }

    return finish;
}


//algoritmo de selección mediante librería aleatoria por semilla

int main(int argc, char *argv[]){

    int seed;
    if(atoi(argv[1])!=0){
        seed = atoi(argv[1]);
    }else{
        seed = time(NULL);
        cout<<"\nSeed null: "<<seed;
    }

    Aleatorio *al = new Aleatorio(seed);


    prueba variable;
    list<prueba> lista1, lista2,aux;
    list<prueba>::iterator it;

    for(short i=0;i<atoi(argv[2]);i++){
        //variable.ingresa((char) round(al->random(65,122)),round(al->random(0,122)));
        variable.ingresa((char)al->int_uniform(65,122),al->int_uniform(0,122));
        lista1.push_back(variable);
    }

    cout<<"\nSelecciona\n";
    cout<<"\nIngresan: "<<lista1.size();
    mostrar(lista1);
    lista1 = seleciona(al, lista1);
    cout<<"\n\nCantidad total: "<<lista1.size();
    mostrar(lista1);

    delete al;

    return 0;
}