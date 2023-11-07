#include <iostream>
#include <fstream>
#include "Aleatorio.h"

using namespace std;

//generación de un archivo de datos con nombre aleatorio

int main(int argc, char *argv[]){

    string out;
    ofstream fout;
    char *salida;
    Aleatorio *rnd = new Aleatorio(stoi(argv[1]));
    int rnd_file = rnd->int_uniform(100000,900000);

    //crea archivo
    out = to_string(rnd_file)+".txt";
    fout.open(out);
    fout<<"Archivo de prueba";
    fout.close();
    
    //genera comando de borrado
    out = "rm "+out;
    salida = &out[0];
    
    //borra archivo
    system(salida);
    cout<<"Salida del pc guardado: "<<out;

    return 0;
}