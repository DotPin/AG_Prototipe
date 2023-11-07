#include <iostream>
#include <fstream>
#include <cstring>
#include "Aleatorio.h"

using namespace std;

//tokenizador, busca token de un archivo y lo modifica.

string tokeniza(string entrada,string fl,string mdf){

    char *tkn,*chg;
    string token="", salida;

    for (size_t i = 0; i < entrada.length(); i++){
        if(entrada.at(i) == ' ' || entrada.at(i) == '\n') {
            if (token == fl) token = mdf;
            salida = salida + token + " ";
            if(entrada.at(i) == '\n') salida = salida + '\n';
            token = "";
        }else{
            token = token + entrada.at(i);
        }
    }
    return salida;

}

void lee_archivo(string entrada,string fl,string mdf){
    ifstream fin;
    string ofile,line;

    fin.open(entrada);
    while(getline (fin, line)){
        line = line +"\n";
        cout << tokeniza(line,fl,mdf);
    }
    fin.close();

}

int main(int argc, char *argv[]){

    lee_archivo(argv[1],argv[2],argv[3]);

    return 0;
}
