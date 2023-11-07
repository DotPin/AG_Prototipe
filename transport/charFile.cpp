#include <iostream>
#include <fstream>      // std::ofstream

using namespace std;

//programa que permite generar archivos de salida con fecha

int main(int argc, char *argv[]){

    ofstream out;

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[30];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
    
    string fout = buf;

    out.open(fout+"_miEquipo_"+"largo_final.txt");
    out.close();

    return 0;
}