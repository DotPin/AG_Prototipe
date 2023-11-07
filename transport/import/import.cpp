#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  //librería para usar transformación de string -> int
#include "cromosoma.h"
#include "Aleatorio.h"


using namespace std; 


//inputs {archivo de datos, archivo de genes, semilla}
int main(int argc, char *argv[]){

    string text,linea,aux;
    short row=0;
    int cnt=0;
    bool flag=false;
    ifstream fin;

    Aleatorio *rnd = new Aleatorio(stoi(argv[3]));
    cromosoma crm;
    
    vector<string> titulo;
    vector<string> parametros;
    vector<string> data;
    vector<string> genes;

    fin.open(argv[1]);
    getline(fin,text,' ');

    for (size_t i = 0; i < text.size(); i++){
        if(text.at(i)!='\n'){
            linea = linea + text.at(i);
        }else{
            linea = linea + '\n';
            //extrae valores descripción de experimentos
            if(row==0){
                for (size_t i = 0; i < linea.size(); i++){
                    if(linea.at(i)!=',' && linea.at(i)!='\n'){
                        aux = aux + linea.at(i);
                    }else{
                        titulo.push_back(aux);
                        aux="";
                    }
                }
                row = row + 1;

            //extrae segunda fila de parámetros
            }else if(row==1){
                for (size_t i = 0; i < linea.size(); i++){
                    if(linea.at(i)!=',' && linea.at(i)!='\n'){
                        aux = aux + linea.at(i);
                    }else{
                        parametros.push_back(aux);
                        aux="";
                    }
                }
                row = row + 1;
            
            //extrae los datos
            }else{
                for (size_t i = 0; i < linea.size(); i++){
                    if(linea.at(i)!=',' && linea.at(i)!='\n'){
                        aux = aux + linea.at(i);
                    }else{
                        if(aux==titulo[9]) {
                            if(cnt==stoi(titulo[1])){
                                flag=true;
                            }
                            cnt++;
                        }
                        if(flag){
                            data.push_back(aux);
                        }
                        aux="";
                    }
                }
            }
            linea="";
        }
    }
    fin.close();

    /*
    for (size_t i = 0; i < data.size(); i++){
        cout<<data[i]<<"\n";
    }*/

    crm = cromosoma(stoi(titulo[3]),stof(data[data.size()-2]),rnd);
    
    fin.open(argv[2]);
    getline(fin, text,' ');
    cnt=0;
    //importa genes mejor tubo
    for (size_t i = 0; i < text.size(); i++){
        if(text.at(i)!='\n'){
            aux = aux + text.at(i);
        }else{
            crm.gen[cnt] = stoi(aux);
            cnt++; 
            aux="";
        }
    }
    //importa radios del mejor tubo
    for (size_t i = 2; i < data.size()-2; i++){
        crm.r_a[i-2] = stof(data[i]);
    }

    cout<<"Data Importada:\n";
    cout<<"Radios:";
    for (size_t i = 0; i < crm.n_e; i++){
        cout<<crm.r_a[i]<<"|";
    }
    cout<<"\nGenes: ";
    for (size_t i = 0; i < crm.n_e; i++){
        cout<<crm.gen[i]<<"|";
    }
    cout<<"\nLargo: "<<crm.largo;
    
    return false;
}