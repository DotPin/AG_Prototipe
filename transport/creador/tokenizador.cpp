#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//tokenizador, busca token de un archivo y lo modifica.

string tokeniza(string entrada,string fl, string mdf){

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
