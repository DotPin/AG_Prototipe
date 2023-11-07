#ifndef TOKENIZADOR_H
#define TOKENIZADOR_H
#include <vector>
#include <string>

using namespace std;

class tokenizador{
        vector<string> locales;
    public:
        tokenizador(vector<string> archivos);
        ~tokenizador();
        string lee_archivo(vector<string> remotos);
        string tokeniza(string entrada,string fl, string mdf);

};


#endif