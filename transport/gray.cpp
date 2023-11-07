#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

//transformación de código binario usando código gray

string bin_to_gray(string in){
    string out;
    int len= in.length();
    for (int i = 0; i < len; i++)
    {
        if(i==0){
            out = in[i];        
        }else{
            if (in[i-1]==in[i])
            {
                out = out +"0";
            }else{
                out = out + "1";
            }
        }
    }
    
    return out;
}

string gray_to_bin(string in){
    string out;
    int len = in.length();
    out = in[0];
    for (size_t i = 1; i < len; i++)
    {
        if (in[i]==out[i-1])
        {
            out=out+"0";
        }else{
            out=out+"1";
        }
        
    }
    return out;
    
}



int main(int argc, char *argv[]){

    int valor, divi, cm=0, cnt_bin=19,corte;
    short mod;
    string salida,gr="";

    cout<<"Ingrese valor decimal: ";
    cin>>valor;

    do{
        mod = valor%2;
        salida = to_string(mod)+salida;
        valor = valor/2;
    }while(valor!=0);
    
    cout<<"Salida binaria: "<<salida<<" largo:"<<salida.length()<<"\n";
    gr = bin_to_gray(salida);
    cout<<"Salida en gray: "<<gr<<"\n";
    cout<<"Retorno de gray: "<<gray_to_bin(gr)<<"\n";
    cm=0;
    for(int b=(salida.length()-1);b>=0;b--){
        //cm = cm + salida[b]*pow(2,salida.length()-b-1);
        cm = cm + (salida[b]-'0')*pow(2,salida.length()-b-1);
        //cout<<b<<"|"<<salida[b]<<"|"<<cm<<"\n";
    }

    cout<<"\nValor ingresado: "<<cm;

    return 0;
}