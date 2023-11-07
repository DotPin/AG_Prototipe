#include <iostream>

using namespace std;

//permite ingresar comandos, y ejecutarlos usando ejecutable binario c++

int main(int argc, char *argv[]){

    string entrada;
    char *trf;
    cout <<"Ingrese comando: \n";
    getline(cin,entrada);
    trf = &entrada[0];
    cout<<"Comando: "<<trf<<" Ingresado: "<<entrada;
    system(trf);

    return 0;
}