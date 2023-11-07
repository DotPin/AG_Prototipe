#include "prueba.h"
#include <cstdlib>  
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include <list>

using namespace std;

//Ejercicio cual mediante una lista de objetos, buscar en un índice y modificar su contenido.

int main(int argc, char *argv[]){

    int ingreso,valor;
    char letra;

    prueba variable;
    list<prueba> test;
    list<prueba>::iterator it;

    for(short i=0;i<27;i++){
        variable.ingresa((char)i+64,i);
        test.push_back(variable);
    }

    for(it = test.begin(); it!=test.end(); it++){
        cout<<it->name<<" | "<<it->valor<<"\n";
    }
    cout<<"\n Largo elementos: "<<test.size();
    do{
        cout<<"\nIngrese un valor un índice a modificar: \n";
        cin>>ingreso;
    }while(ingreso<-1 && ingreso>20);

    cout<<"\n Ingrese un valor a modificar: ";
    cin>>valor;
    cout<<"\n Ingrese una palabra un caracter: ";
    cin>>letra;

    it=test.begin();
    advance(it,ingreso);

    it->name=letra;
    it->valor=valor;
    cout<<"\nValor modificado en índice:"<<ingreso<<"\n";
    cout<<"\n"<<it->name<<" | "<<it->valor<<"\n";
    cout<<"\n---------------------------\n";

    for(it = test.begin(); it!=test.end(); it++){
        cout<<it->name<<" | "<<it->valor<<"\n";
    }

}