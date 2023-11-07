#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  //librería para usar transformación de string -> int

using namespace std; 

int main(int argc, char *argv[]){

    string text,line,aux;
    short row=0,aux2=0;
    int r,c,cnt=0;
    bool flag=false;
    ifstream fin;
    
    vector<string> titulo;
    vector<string> parametros;
    vector<string> data;

    fin.open(argv[1]);
    getline(fin, line,' ');
    for (size_t i = 0; i < line.size(); i++){
        if(line.at(i)!='\n'){
            aux = aux + line.at(i);
        }else{
            cout<<stoi(aux)<<'\n';
            aux="";
        }
    }
    
    return 0;
}    
