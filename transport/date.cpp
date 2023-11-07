#include <ctime>
#include <iostream>     // cout
#include <fstream>      // std::ofstream
#include <cstring>
#include "prueba.h"
#include "Aleatorio.h"

using namespace std;

//genera un archivo de salida .csv con escritura de información.

int main(int argc, char *argv[]){

    
    Aleatorio *rnd = new Aleatorio(time(NULL));
    ofstream out_file;

    //parámetros del conjunto date
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
    string fout = buf;
    fout = fout+".csv";

    list<prueba>::iterator it;
    list<prueba> test;
    prueba elemento;

    //creamos archivo de salida con los datos
    out_file.open(fout);

    if(out_file.is_open()){
        cout<<"\n Output file successfule performed \n";
    }else{
        cout<<"\nError opening file, end execution\n";
        return(0);
    }

    out_file<<"Población: "<<26<<",Elementos: "<<2<<",P.Mutación: "<<0.001<<",P.Cruzamiento"<<0.45<<"\n";
    out_file<<"Generación"<<",Tubo";
    for(int r=1;r<3;r++){
        out_file<<",e"<<r;
    }
    out_file<<"\n";

    //leno lista de elementos
    for (size_t i = 65; i < 91; i++){
        elemento.ingresa((char)i,i-65);
        test.push_back(elemento);
    }
    for (it=test.begin(); it!=test.end(); it++){
        out_file<<1<<","<<it->name<<","<<it->valor<<","<<it->valor*rnd->random(0,1)<<"\n";
    }
    
    delete rnd;
    out_file.close();

    return(0);
}
