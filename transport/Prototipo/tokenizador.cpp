#include "tokenizador.h"
#include <iostream>
#include <vector>
#include <fstream> 

using namespace std;

tokenizador::tokenizador(vector<string> archivos){
    locales = archivos;
}

tokenizador::~tokenizador(){}

string tokenizador::lee_archivo(vector<string> remotos){
    string buffer, out="",line;
    vector<string> texto;
    ifstream fin;
    fin.open(locales[0]);
    while(getline(fin,line)){
        texto.push_back(line + "\n");
    }
    fin.close();
    line="";
    
    for (size_t i = 1; i < remotos.size(); i++){
        for (size_t j = 0; j < texto.size(); j++){
            buffer = texto[j];
            for(size_t k=0; k<buffer.size(); k++){
                if(buffer.at(k)!= '\n'){
                    line = line + buffer.at(k);
                }else{
                    line = line + "\n";
                    out = out + tokeniza(line,locales[i],remotos[i]);
                    line="";
                }
            }
            texto[j] = out;
            out="";
        }
    }
    for (size_t i = 0; i < texto.size(); i++){
        out = out + texto[i];
    }
    return out;
}

string tokenizador::tokeniza(string entrada,string fl, string mdf){

    string salida="", token="",aux="";
    bool flag=true;

    for (size_t i = 0; i < entrada.length(); i++){
        switch(entrada.at(i)){
            case ' ':
                salida = salida + token + ' ';
                token="";
                break;
            case '\n':
                salida = salida + token + '\n';
                token="";
                break;
            case '"':
                if(flag) {
                    aux = salida + token + entrada.at(i);
                    token="";
                    flag=false;
                }else{
                    flag=true;
                    if(token == fl){
                        token = mdf;
                    }
                    salida = aux + token + entrada.at(i);
                    token="";
                    aux="";
                }
                break;
            default:
                token = token + entrada.at(i);
                break;
        }
    }
    
    return salida;
}