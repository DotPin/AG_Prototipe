#include "prueba.h"
#include <cstdlib>  
#include <stdlib.h>     /* srand, rand */
#include "Aleatorio.h"
#include <iostream>
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include <list>

using namespace std;

int main(int argc, char *argv[]){

    srand(time(NULL)); //cambia valores aleatorios cada vez q se ejecuta con otro tiempo pedido a memoria

    Aleatorio *al = new Aleatorio();

    prueba variable;
    list<prueba> lista1, lista2,aux;
    list<prueba>::iterator it;

    for(short i=0;i<60;i++){
        variable.ingresa((char)al->rango(50),al->rango(50));
        lista1.push_back(variable);
    }

    aux = lista1;

    for(it=lista1.begin();it!=lista1.end();it++){
        cout<<"\n[C]: "<<it->name<<" [V]: "<<it->valor;
    }
    cout<<"\n";
    int rnd=0;
    for(short j=0;j<lista1.size();j++){
        for(it=lista1.begin();it!=lista1.end();it++){
            rnd = al->rango(14);
            if(it->valor < rnd ){

                cout<<"\nValor: "<<it->valor<<" CMP:"<<rnd;
                //lista1.splice(it,lista2);

                //obtiene nodo buscado y lo enlaza en lista2, destruyendo la lista1
                lista2.splice(lista2.end(),lista1,it);

                //restauro lista1 para continuar con los parámetros del for
                //lista1 = aux;

                break;

            }

        }

    }

    cout<<"\nSalida\n";
    cout<<"\nLista 1\n";
    for(it=lista1.begin();it!=lista1.end();it++){
        cout<<"\n[C]: "<<it->name<<" [V]: "<<it->valor;
    }
    cout<<"\n";

    cout<<"\nLista 2\n";
    for(it=lista2.begin();it!=lista2.end();it++){
        cout<<"\n[C]: "<<it->name<<" [V]: "<<it->valor;
    }
    cout<<"\n";


    
    return 0;
}
