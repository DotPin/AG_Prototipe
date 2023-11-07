#include <iostream>
#include <fstream>

using namespace std;

//algoritmo que guarda el nombre de máquina y elimina un archivo de texto 

int main(int argc, char *argv[]){

    string out;
    ifstream fin;

    system("whoami >> name.txt");
    fin.open("name.txt");
    while(!fin.eof()){
        fin>>out;
    }
    system("rm name.txt");
    cout<<"Salida del pc guardado: "<<out;

    return 0;
}

