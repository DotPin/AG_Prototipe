#ifndef CROMOSOMA_H
#define CROMOSOMA_H
#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include "Aleatorio.h"
using namespace std;

class cromosoma{
      
      Aleatorio *rndm;       
      
      public:
            //colección de radios, 
            //valor de ajuste, 
            //largo tubo, 
            //variables de subparticion nodal inicial y final
            float *r_a, fit=6500, largo=0.5, a,b ;

            //bandera de activación para variación de largos
            bool flag=false;

            //componente de genes por radio
            //numero de elememtos forma
            //contador de mejores
            //cantidad de precisión binaria
            //corte de aproximacion binaria
            int *gen, n_e, count_best=0,cantidad_bin, corte=5;

            //ID del individuo
            string name;

            cromosoma(){};
            cromosoma(int a,float l, Aleatorio *rnd);
            void Eval();
            int generador(int bits);
            float transformador(int crm);
            int transformadorInv(float ra);
            int cnt_bin();
            string nombre();
            list<cromosoma> probabilidades(list<cromosoma> lista);
            
};

#endif
