#include "prueba.h"
#include "Aleatorio.h"
#include <cstdlib>  
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include <list>

using namespace std;

//algoritmo que desordena una lista enlazada

list<prueba> shuffle(list<prueba> lista){
    Aleatorio *rnd = new Aleatorio(time(NULL));

    list<prueba>::iterator it,swp;

    for(int i=0; i<lista.size();i++){
        it=lista.begin();
        swp=lista.begin();
        advance(it,rnd->rango(lista.size()+1));
        advance(swp,rnd->rango(lista.size()+1));
        iter_swap(swp,it);
    }

    delete rnd;

    return lista;
}

int main(int argc, char *argv[]){

    Aleatorio *rnd = new Aleatorio(time(NULL));
    int rn=0;
    prueba elem;
    
    list<prueba> test,aux;
    list<prueba>::iterator it;


    for(int i=0;i<30;i++){
        rn = rnd->random(64,80);
        elem.ingresa((char)rn,rnd->rango(15));
        test.push_back(elem);
    }

    for(it=test.begin();it!=test.end();it++){
        cout<<"\n"<<it->name<<" | "<<it->valor;
    }
    cout<<"\nTamaño inicial: "<<test.size()<<"\n";

    for(int i=0;i<10;i++){
        for(it=test.begin();it!=test.end();it++){
            it->valor = it->valor -1 ;
            if((it->valor)<1){
                rn = rnd->random(54,63);
                elem.ingresa((char)rn,rnd->rango(10));
                cout<<"\niter"<<i<<" out:"<<it->name<<"|"<<it->valor<<" in:"<<elem.name<<"|"<<elem.valor;
                aux.push_back(elem);
                it = test.erase(it);
            }
        }
    }

    rn = aux.size();
    for(int j=0;j<rn;j++){
        it=aux.begin();
        if(it!=aux.end()){
            test.splice(test.end(),aux,it);
        }else{
            break;
        }

    }

    test = shuffle(test);
    

    cout<<"\nTamaño final: "<<test.size()<<"\n";

    for(it=test.begin();it!=test.end();it++){
        cout<<"\n"<<it->name<<" | "<<it->valor;
    }

    delete rnd;

    return 0;
}