#include <cstdlib>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

//prototipo de transformación binaria -> entera, 
//entera -> binaria junto con valor de precisión.

int main(){

    int valor, divi, cm=0, cnt_bin=19,corte;
    short mod;
    string salida,bin="";

    cout<<"Ingrese valor a binario: ";
    cin>>valor;

    do
    {
        cout<<"Ingrese valor de corte: ";
        cin>>corte;
        if(corte>cnt_bin){
            cout<<"\nValor e corte por default";
            corte=0;
            break;
        }
    } while (corte>cnt_bin);
    

    do{
        mod = valor%2;
        salida = to_string(mod)+salida;
        valor = valor/2;
    }while(valor!=0);
    
    valor = cnt_bin-salida.length();
    
    for(int i=0;i<valor;i++){
        salida = "0"+salida;
    }

    cout<<"Salida binaria: "<<salida<<" largo:"<<salida.length()<<"\n";

    cm=0;
    for(int b=(salida.length()-1);b>=(cnt_bin-corte);b--){
        cm = cm + (salida[b]-'0')*pow(2,salida.length()-b-1);
        //cout<<b<<"|"<<salida[b]<<"|"<<cm<<"\n";
    }

    cout<<"\nValor ingresado: "<<cm;

    return 0;
}