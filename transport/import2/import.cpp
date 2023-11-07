#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  //librería para usar transformación de string -> int
#include <list>
#include "cromosoma.h"
#include "Aleatorio.h"


using namespace std; 
Aleatorio *rnd = new Aleatorio(5);

list<cromosoma> importa_ra(list<cromosoma> pob,vector<float> radios,float l){
    cromosoma crm = cromosoma(radios.size(),l,rnd);
    
    for (size_t i = 0; i < radios.size(); i++){
        crm.r_a[i] = radios[i];
    }
    pob.push_back(crm);

    return pob;
}

list<cromosoma> importa_gen(list<cromosoma> pob,vector<int> genes,int idx){
    list<cromosoma>::iterator it=pob.begin();

    for (int i = 0; i < idx; ++i){
        it++;
    }
    
    for (size_t i = 0; i < genes.size(); i++){
        it->gen[i] = genes[i];
    }
    return pob;
}


//inputs {archivo de datos, archivo de genes, semilla}
int main(int argc, char *argv[]){

    string text,linea,aux;
    short row=0;
    int cnt=0;
    bool flag=false;
    ifstream fin;

    list<cromosoma> pob;
    
    vector<string> titulo;
    vector<string> parametros;
    vector<string> data;
    vector<int> genes;
    vector<float> radios;
    vector<float> largos;


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
            
            //extrae los datos de la última generación
            }else{
                for (size_t i = 0; i < linea.size(); i++){
                
                    if(linea.at(i)!=',' && linea.at(i)!='\n'){
                        aux = aux + linea.at(i);
                    }else{
                        if(aux==titulo[9]) {
                            flag=true;
                        }
                        if(flag){
                            data.push_back(aux);
                        }
                        aux="";
                    }
                    if(linea.at(i)=='\n' && flag){
                        data.push_back("\n");
                    }
                }
            }
            linea="";
        }
    }
    fin.close();

    //dato de largos
    for (size_t i = stoi(titulo[3])+2; i < data.size(); i++){
        if(data[i+1]=="\n"){
            i=i+stoi(titulo[3])+3;
        }else{
            largos.push_back(stof(data[i]));
        }
    }
    
    //dato de radios
    cnt=0;
    for (size_t i = 2; i < data.size(); i++){
        if(data[i+2]=="\n"){
            i=i+4;
            pob = importa_ra(pob, radios,largos[cnt]);
            cnt++;
            radios.clear();
        }else{
            radios.push_back(stof(data[i]));
        }
    }
    
    list<cromosoma>::iterator it;

    fin.open(argv[2]);
    getline(fin, text,' ');
    //importa genes de últma generación
    cnt=0;
    for (size_t i = 0; i < text.size(); i++){
        if(text.at(i)!=',' && text.at(i)!='\n'){
            aux = aux + text.at(i);
        }else{
            genes.push_back(stoi(aux));
            aux="";
        }
        if (text.at(i)=='\n'){
            pob = importa_gen(pob,genes,cnt);
            cnt++;
            genes.clear();
        }
    }

    cout<<"****Datos Importados********\n";
    for (it=pob.begin(); it !=pob.end(); ++it){
        for (int i = 0; i < it->n_e; ++i){
            cout<<it->r_a[i]<<" ";
        }
        cout<<"\n";
        for (int i = 0; i < it->n_e; ++i){
            cout<<it->gen[i]<<" ";
        }
        cout<<"\n";
    }
    return false;
}