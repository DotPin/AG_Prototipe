#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <cmath>
#include <math.h>       /*Incuye variable pi en M_PI*/
#include "cromosoma.h"
#include "Aleatorio.h"

using namespace std;

int cromosoma::cnt_bin(){
    return (int)(log(((b-a)*pow(10,corte))-1)/log(2));
}

int cromosoma::generador(int bits) {

  int bin=0,rn;
  for (int i=0; i<bits; i++) {
    rn = rndm->int_uniform(0,1);
    bin = bin + (int)pow(rn*2, i);
  }
  return bin;
}

string cromosoma::nombre(){

  //Próximo desarrollo: Generación determinista de nombres.
  Aleatorio *rn = new Aleatorio(rndm->getSeed());
  string out="";
  for (size_t i = 0; i < 10; i++){
    if(rn->int_uniform(0,1) ==0) out = out + (char)rn->int_uniform(65,90);
    else out = out + (char)rn->int_uniform(97,122);
  }
  delete rn;
  return out;
}

void cromosoma::Eval(){
    
    std::ofstream myfile;
    std::ifstream fin;
    string line;

    //exporto los radios del individuo a octave
    myfile.open("radios.csv");
    for(short l=0;l<n_e;l++){
      myfile<<r_a[l]<<"\n";
    }
    myfile.close();

    if(flag){
      //importar variabilidad del largo mediante inputs
      largo = rndm->float_uniform(0.5,2);
      //exporto largo del tubo en archivo
      myfile.open("largo.txt");
      myfile<<largo;
      myfile.close();
    }else{
      //exporto largo del tubo en archivo
      myfile.open("largo.txt");
      myfile<<largo;
      myfile.close();
    }

    //ejecuto octave
    system("octave fem_basico.m");

    //leo archivo de la función objetivo para extraer valor calculado.
    fin.open("f_obj.csv");
    while(!fin.eof()){
        fin>>line;
    }
    fin.close();

    fit = stof(line);
}


float cromosoma::transformador(int crm){
  return (a + crm*((b-a)/(pow(2, cantidad_bin)-1 )));
}

int cromosoma::transformadorInv(float ra){
  return (((ra-a)*(pow(2,cantidad_bin)-1))/(b-a));
}

cromosoma::cromosoma(int num_e,float l,Aleatorio *rnd){
    
    //referenciamos random
    rndm = rnd;

    //incorporar generación aleatoria de largos
    if(l==0){
      flag =true;
      //largo = rndm->float_uniform(0.5,1.2);
    }else largo = l;
    

    //Se establece recorrido del tubo, con nivel de precisión generadora. 
    //delimita la cantidad de bits por gen   
    a = largo/64;
    b = largo/2;

    cantidad_bin = cnt_bin(); 

    //cantidad de elementos de radio
    n_e=num_e;

    //arreglo de radios en valor real por índice
    float *radios = new float[n_e];

    //arreglo de genes en valor entero por índice
    int *genes = new int[n_e];

    r_a = radios;
    gen = genes;

    name = nombre();

    //inicio la cantidad de radios con sus genes respectivos.
    for(short l=0;l<n_e;l++){
      //establece gen con un valor entero mediante cálculo binario aleatorio, 
      //sobre el recorrido del tubo.
      gen[l] = generador(cantidad_bin); 

      //calcula valor de radio por elemento según el gen.
      r_a[l] = transformador(gen[l]);    
    }

}