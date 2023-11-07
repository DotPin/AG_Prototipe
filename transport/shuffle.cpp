// random_shuffle example
#include <iostream>     // std::cout
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <list>
#include <algorithm>    // std::copy
#include "prueba.h"
#include "Aleatorio.h"

using namespace std;

//algoritmo que genera intercambios de valores en una lista enlazada.
 
list<prueba> swp(list<prueba> lista){
    Aleatorio *rnd = new Aleatorio();
    cout<<"\nInicia swap";

    int len = lista.size(),r=0;
    list<prueba>::iterator it,sw;

    for(int i=0; i<len;i++){
        it=lista.begin();
        sw=lista.begin();
        advance(it,rnd->rango(lista.size()+1));
        advance(sw,rnd->rango(lista.size()+1));
        cout<<"\n Intercambia: "<<it->name<<" / "<<sw->name;

        iter_swap(sw,it);
    }
    
    return lista;
}


int main (int argc, char *argv[] ) {
    srand(time(NULL)); 
    
    list<prueba>::iterator it;
    
    //srand ( unsigned ( time(0) ) );
    list<prueba> numeros,n_aux;
    int i=0,len=0;
    prueba aux;
    
    // ingreso valores a través de una clase
    for (i=65; i<91; ++i){
        aux.ingresa((char)i,i);
        numeros.push_back(aux); 
    } 
    cout << "\nMi lista contiene:\n";
    for (it=numeros.begin(); it!=numeros.end(); it++){
        cout <<it->name<<" | "<<it->valor ;
        cout << '\n';
    }
    len= numeros.size();
    cout<<"\nTamaño in: "<<len;

    //generar swaping eliminando e insertando elementos
    numeros = swp(numeros);

    cout << "\nMi lista desordenada:\n";
    for (it=numeros.begin(); it!=numeros.end(); it++){
        cout <<it->name<<" | "<<it->valor ;
        cout << '\n';
    }
    cout<<"\nTamaño out: "<<numeros.size();


    return 0;

}