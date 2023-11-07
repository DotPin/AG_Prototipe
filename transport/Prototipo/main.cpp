#include <iostream>
#include <fstream>
#include <vector>
#include "Aleatorio.h"
#include "tokenizador.h"

using namespace std;

//Tokenizador que permite la modificación del contenido  de un archivo
//para la generación de uno nuevo.

string nombre(Aleatorio *rnd){

  string out="";
  for (size_t i = 0; i < 10; i++){
    out = out + (char)round(rnd->int_uniform(65,90));
  }
  return out;
}


int main(){

    ofstream fout;

    char *trf;  //transforma string -> char para comando en terminal

    Aleatorio *rnd = new Aleatorio(time(NULL));
    vector<string> f_locales = {"test.m","largo.txt","radios.csv","f_obj.csv"};
    vector<string> f_remotos = {nombre(rnd)+".m", nombre(rnd)+".txt", nombre(rnd)+".csv", nombre(rnd)+".csv"};

    tokenizador *tkn = new tokenizador(f_locales);

    fout.open(f_remotos[0]);
    fout<<tkn->lee_archivo(f_remotos);;
    fout.close();
    

    delete tkn;
    delete rnd;

    return 0;
}