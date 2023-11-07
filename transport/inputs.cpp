#include <iostream>

using namespace std;

//Algoritmo para poder bifurcar procedimientos con respecto a las entradas por consola.

int main(int argc, char *argv[]){

    string tm;

    cout<<"Inputs Data: "<<argc<<"\n";
    if(argc < 3){
        cout<<"Input de data por archivo\n";
        for (size_t i = 1; i < argc; i++){
            cout<<argv[i]<<" ";
        }
    }else{
        cout<<"Input de data manual\n";
        for (size_t i = 1; i < argc; i++){
            cout<<argv[i]<<" ";
        }
        
    }
    tm= argv[1];
    cout<<"\n"<<tm.size();

    return 0;
}