#include <cstdlib>  
#include <iostream>
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include <list>

using namespace std;

//prototipo de traspaso de elementos entre listas enlazadas.

int main(int argc, char *argv[]){

    list<int> lista1,lista2;
    list<int>::iterator it;

    for(int i=0;i<10;i++){
        lista1.push_back(i);
    }
    for(int i=0;i<10;i++){
        lista2.push_back(i%2);        
    }
    cout<<"\nLista inicial 1: ";
    for(it=lista1.begin();it!=lista1.end();++it){
        cout<<" "<<*it;
    }

    cout<<"\nLista inicial 2: ";
    for(it=lista2.begin();it!=lista2.end();++it){
        cout<<" "<<*it;
    }


    it = lista1.begin();
    ++it;
    ++it;
    ++it;


    lista1.splice(it,lista2);

    lista2.splice(lista2.begin(),lista1,it);

    /*it = lista1.begin();
    advance(it,3);

    lista1.splice(lista1.begin(), lista1, it, lista1.end());

    cout<<"\n Lista final 1: ";
    for(it=lista1.begin();it!=lista1.end();++it){
        cout<<" "<<*it;
    }*/

    cout<<"\n Lista final 2: ";
    for(it=lista2.begin();it!=lista2.end();++it){
        cout<<" "<<*it;
    }
    cout<<"\n";


    return 0;
}