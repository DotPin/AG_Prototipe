//Algoritmo genético
//Desarrollado por: Diego Ignacio Rojas Asenjo

#define _USE_MATH_DEFINES       /*Permite importar las librerías matemáticas math.h*/
#define tope 650

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /*permite ocupar otro tiempo para la memoria */
#include <chrono>       /*permito usar delay*/
#include <thread>       /*permito usar delay*/
#include <cstdlib>  
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>       /*clase permite usar transformación binaria*/
#include <cmath>        /* permite usar round y funciones trigonométricas*/
#include <math.h>
#include "module/Aleatorio.h"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

//int epocas = 0;
float pm=0.009;                             //probabilidad de mutacion  
float pc=0.53;                              //probabilidad de cruzamiento
int cantidad;             //Población de cromosomas a ejecutar
float salida;
int cnt_binaria=0;                          //cantidad de bits para cromosoma
int corte=5;                              //valor de precisión en el cálculo de la cantidad de bits (10^corte) (parametro relacionado largo de arreglo de bits de cromosoma)
float a=-5.12,b=5.12;                     //intervalos [a,b] corresponden al dominio de la función a optimizar
float gbestx=100, gbesty=100, gbest=100,gbest_locx,gbest_locy;   // mejor cromosoma , ajuste y localizacion del mejor global
int evals = 0, evals_to_best = 0;         //número de evaluaciones, sólo para despliegue
float suma=0,q=0;

float xx[650][650],yy[650][650];

void reinicio(){
    suma=0;
    q=0;
}

//----------------------------------------cuenta la cantidad de bits del cromosoma
void cnt_bin(){                        //define la cantidad de bits de la palabra binaria, que para estos casos usaremos para la representacion decimal solamente
  cnt_binaria = (int)(log(((b-a)*pow(10,corte))-1)/log(2));
}

//------------------------------funcion rastrigin para Z
float rastrigin(float x, float y){        //evalua función rastrigin en Z
  return (pow(x,2)-10*cos(2*M_PI*x))+ (pow(y,2)-10*cos(2*M_PI*y)) + 20;
}

void mesh_x(float xx[tope][tope]){              //fusionar las funsiones mesh en 1 sola.
    float intervalo=((2*5.12)/650),inicio=-5.12;
    for(int i=0;i<650;i++){
        for(int f=0;f<650;f++){
            xx[f][i]=inicio;
            
        }
        inicio = inicio+intervalo;
    }
}

void mesh_y(float yy[tope][tope]){
    float intervalo=((2*5.12)/650),inicio=-5.12;
    for(int i=0;i<650;i++){
        for(int f=0;f<650;f++){
            yy[i][f]=inicio;
            
        }
        inicio = inicio+intervalo;
    }
}

int busqueda(float matriz[tope][tope], float v, bool flag){
    int salida=0;
    for(short i=0; i<tope;i++){
    if (flag){    //true revisa valores para X
      if (matriz[0][i]>=v){
        salida = i;
        break;
      }
    }
    else{        //false revisa valores para Y
      if (matriz[i][0]>=v){
        salida = i;
        break;
      }
    }
    
  }
  return salida;
    
}

//---------------------------Funcion binaria
int binario(int bits) {
  int bin=0;
  int rnd;
  for (int i=0; i<bits; i++) {
    rnd = (int)round((rand() / (RAND_MAX+1.)));
    bin = bin + (int)pow(rnd*2, i);
  }
  return bin;
}

float optimizador(int crm){
  float rst= a + crm*((b-a)/(pow(2, cnt_binaria)-1));
  return rst;
}

class cromosomas{
    public:
        float x, y, z, fit=100;                 // cromosoma x, y, z para evaluacion rastrigin y el ajuste,  
        float px, py,ploc_x,ploc_y, pfit;     // cromosomas óptimos y ajuste de la mejor solucion de cromosoma
        int crm1,crm2;                      //registro de cromosomas de x, y representados en enteros desde binarios
        float p,q_ac;                      //valor de cromosoma para x e y, probabilidad
        int loc_x,loc_y,nm;                 //valores geográficos cromosoma (x,y) , identificador cromosoma
        
        cromosomas();
        cromosomas(int a); 
        
        float Eval();
};

cromosomas::cromosomas(){}

cromosomas::cromosomas(int a){
    
    crm1 = binario(cnt_binaria);
    crm2 = binario(cnt_binaria);
            
    x = optimizador(crm1);    //calcula valor x para optimizar en rastrigin
    y = optimizador(crm2);    //calcula valor y para optimizar en rastrigin
    
    loc_x = busqueda(xx,x,true);
    loc_y = busqueda(yy,y,false);
    
    nm=a;
    //cout<<"\n Cromosoma:"<<nm<<" crm1:"<<crm1<<" crm2:"<<crm2<<" x:"<<x<<" y:"<<y;
}

float cromosomas::Eval(){
    evals++;
    z = rastrigin(x,y);     //eliminar variable z por fit
    suma = suma + z;    //se realiza la suma te los ajustes para la ruleta
    fit = z;
    //cout<<" \nEvalua: "<<z<<" x:"<<x<<" y:"<<y;
    if(fit <= pfit){ // actualiza local best si es mejor
        pfit = fit;
        px = x;
        py = y;
        ploc_x = loc_x;
        ploc_y = loc_y;
    }
    if (fit <= gbest){ // actualiza global best
        gbest = fit;
        gbestx = x;
        gbesty = y;
        gbest_locx = loc_x;
        gbest_locy = loc_y;
        evals_to_best = evals;  /*guarda el numero de evaluaciones que encontró el global*/
        
    }
    return fit; //retorna el mejor ajuste 
}

cromosomas op_crm(cromosomas k,cromosomas b){
  if (k.fit<=gbest){
    b = k;
  }
  return b;
}

cromosomas ajustes(cromosomas k){
    k.x = optimizador(k.crm1);
    k.y = optimizador(k.crm2);
    
    k.loc_x = busqueda(xx,k.x,true);
    k.loc_y = busqueda(yy,k.y,true);
    
    return k;
}

cromosomas *probabilidades(cromosomas *k){
    for(int i=0;i<cantidad;i++)     //probabilidad individual
        k[i].p = k[i].z/suma;
    
    for(int i=0;i<cantidad;i++){     //probabilidad acumulada
        q = q + k[i].p;
        k[i].q_ac=q;
    }
    
    return k;
}

//*****************************************INICIO PROCESO SELECCION**************************************************************

cromosomas* shuffle(cromosomas *ak){        //función que desordena los elementos al interior del arreglo objetos de cromosomas
  int rnd;
  cromosomas aux = cromosomas(0);
  for(int i=0;i<cantidad;i++){
    rnd = (rand() % (cantidad-1));
    if(rnd != i) {
      aux = ak[i];
      ak[i] = ak[rnd];
      ak[rnd] = aux;
    }
  }
  return ak;
}

cromosomas* selecciona(cromosomas best, cromosomas *fl, cromosomas *sons){

  Aleatorio *chg = new Aleatorio();

  float rnd=0,op=(best.p+0.004),at=0;    //nos permite crear una cota de numeros aleatorios dentro del optimo
  //cout<<"\nbest: "<<best.nm<<" p:"<<best.p;
  bool flag=true,flag2=true;
  int cnt_round=0;
  int j=0,i=0,v0=0,vt=0,r=0;
  fl = shuffle(fl);                    //desordena lista de cromosomas
  while(i<cantidad){
    v0=i;
    rnd = chg->random(0,op);
    while(j<cantidad && i<cantidad){
      while(r<i && flag){
        if(fl[j].p==sons[r].p && flag2){
          flag = false;
        }
        r++;
      }
      if(fl[j].p<=rnd && flag){
        sons[i]=fl[j];
        i++;
      }
      j++;
      flag=true;
    }
    //********controla y habilita paso de factores repetidos que no completen la selección de barrido único, que produzca un estancamiento. 
    flag2=true;
    vt=i;
    at=(vt-v0)/j;    //<------------el cálculo de la variación me dirá si se producen cambios en el almacenamiento del proceso de selección o si se estanca.
    if(at==0){
      op = op+0.05;    //<------------------cuidar este parámetro, ya que no se sabe a priori si sirve como ponderador escalable
      cnt_round++;
      if(cnt_round==2){
         flag2=false;
         cnt_round=0;
      }
    }
    //*****************************Permite que esta sección ayudar el proceso de selección bajando la escala de aproximación
    j=0;
  }
  return sons;
}

//*****************************************FIN PROCESO SELECCION**************************************************************


int unbinary(int *s){ 
    int acum=0;
    for(int i=0;i<cnt_binaria;i++){
        if((cnt_binaria-1-i)!=0 || s[cnt_binaria-1]!=0) acum = acum + pow(2*s[i],cnt_binaria-1-i);
    }
    return acum;
}

//*****************************************INICIO PROCESO MUTACION1**************************************************************

int construye_bin(int y,int pos){ //recibe fit de cromosoma, posicion de bit a mutar
  string binario=bitset< 19 >( y ).to_string(),pl="";
  short dot=0;
  
  int len;
  len= binario.size();
  int arr[cnt_binaria];
  
  for(int i=len-cnt_binaria;i<len;i++){     //revisar opción de eliminarlo 
    pl = binario[i];
    arr[dot]= stoi(pl);     //convierte string en entero decimal
    dot++;
  }
  
  //DESCOMENTAR PARA REVISAR DESPLIEGUE
  //cout<<"\tAntes dec:"<<y<<"\tBinario:"<<binario;
  
  if (arr[cnt_binaria-1-pos]==0){
    arr[cnt_binaria-pos-1]=1;
  }else{
    arr[cnt_binaria-pos-1]=0;
  }
   
  y = unbinary(arr);
  
  /*cout<<"\tDesp dec:"<<y<<"\tBinario:";
  for(int i=0;i<cnt_binaria;i++){
      cout<<arr[i];
  }
  cout<<" pos"<<pos;*/
        
  return y;
}

cromosomas *mutar_rr1(cromosomas *sons){
    Aleatorio *chg = new Aleatorio();

    int bits=(cnt_binaria*2)*cantidad, total = pm*bits, id_crm,id_bit, idx=0,rnd=0,aux=0;
    int *sel_crm = new int[total];
    int *buffer = new int[bits];
    
    for(short i=0;i<bits;i++){
        buffer[i]=1;
    }
    
    for(short i=0;i<bits;i++){
        rnd = chg->random(0,bits-1);
        if(pm>chg->random(0,1.0) && buffer[rnd]!=0 ){
            
            sel_crm[idx]=rnd;
            buffer[rnd]=0;
            idx++;
        }
        if (idx==total){
            
            break;
        }
        
    }
    
    
    for(short i=0;i<total;i++){
        if(sel_crm[i]!=0){
            id_bit = sel_crm[i]%(cnt_binaria*2);
            id_crm = round(sel_crm[i]/(cnt_binaria*2));
            if (id_bit==0) id_bit=(cnt_binaria*2)-1;
            
            if(id_bit < cnt_binaria){
    
                sons[id_crm].crm1 = construye_bin(sons[id_crm].crm1,id_bit);
                sons[id_crm] = ajustes(sons[id_crm]);
            }else{
    
                sons[id_crm].crm2 = construye_bin(sons[id_crm].crm2,id_bit);
                sons[id_crm] = ajustes(sons[id_crm]);
            }
        }
        
    }
    return sons;
}



cromosomas* mutar_rr0(cromosomas *sons){
    Aleatorio *chg = new Aleatorio();

    short bits=(cnt_binaria*2)*cantidad, total = pm*bits, id_crm,id_bit;
    for(short i=0; i<bits;i++){
        if(pm>chg->random(0,1.0) && total>0){      //evalua la probabilidad de mutacion y cantidad de bits a mutar
            id_crm = round(i/(cnt_binaria*2)); //identifica cromosoma
            id_bit = i%(cnt_binaria*2);         //identifica el bit del cromosoma que muta
            if (id_bit==0) id_bit=(cnt_binaria*2)-1;        //en caso de encontrar bit final dle arreglo, posicionarlo en posicion-1
            if(id_bit<cnt_binaria){
                //DESCOMENTAR PARA REVISAR DESPLIEGUE
                //cout<<"\nEcrm1:"<<sons[id_crm].nm<<" dec:"<<sons[id_crm].crm1<<" x:"<<sons[id_crm].x<<" y:"<<sons[id_crm].y;
                sons[id_crm].crm1 = construye_bin(sons[id_crm].crm1,id_bit);
                sons[id_crm] = ajustes(sons[id_crm]);
                //cout<<"\nScrm1:"<<sons[id_crm].nm<<" dec:"<<sons[id_crm].crm1<<" x:"<<sons[id_crm].x<<" y:"<<sons[id_crm].y;
            }else{
                
                //cout<<"\nEcrm2:"<<sons[id_crm].nm<<" dec:"<<sons[id_crm].crm2<<" x:"<<sons[id_crm].x<<" y:"<<sons[id_crm].y;
                sons[id_crm].crm2 = construye_bin(sons[id_crm].crm2,id_bit-cnt_binaria);
                sons[id_crm] = ajustes(sons[id_crm]);
                //cout<<"\nScrm2:"<<sons[id_crm].nm<<" dec:"<<sons[id_crm].crm2<<" x:"<<sons[id_crm].x<<" y:"<<sons[id_crm].y;
            }
            total--;
        }
        
    }
    return sons;
}


//*****************************************FIN PROCESO MUTACION1**************************************************************




//*****************************************INICIO PROCESO MUTACION2**************************************************************
int swap(int adn,int x, int y){
  string binario=bitset< 19 >( adn ).to_string(),pl="";
  
  short aux=0;
  
  int len;
  len= binario.length();
  int arr[cnt_binaria];
  
  for(int i=0;i<cnt_binaria;i++){     //revisar opción de eliminarlo 
    pl = binario[i];
    arr[i]= stoi(pl);     //convierte string en entero decimal
  }
  
  aux=arr[x];
  arr[x] = arr[y];
  arr[y]=aux;

  adn = unbinary(arr);
  
  return adn;
}


cromosomas* mutacion2(cromosomas *sons){        /////MMODIFICAR ALGORITMO QUE ORIENTE A INDIVIDUOS ESPECÏFICOS NO A TODOS

    Aleatorio *chg = new Aleatorio();
    //Cambios realizados 26 - 07 - 2021, contempla búsqueda por individuo según pm.
    //luego a cromosoma encontrado, busca aleatoriamente bit de  cromosoma parcial a mutar, realiza operación y continua con el siguiente individuo
    cromosomas crm = cromosomas(0);
    int k=0;
    for(int i=0;i<cantidad;i++){      //recorre conjunto de cromosomas
        crm = sons[i];
        if(chg->random(0,1)<pm){           //consulta si cromosoma puede mutar
            for(int j=0;j<cnt_binaria*2;j++){       // recorre el total de bits del cromosoma
                if(chg->random(0,1)<pm){                   //selecciona un bit del cromosoma a mutar según la probabilidad de mutacion, realiza y termina búsqueda
                    k = (int)chg->random(1,cnt_binaria-1);    //corregir para la mutacion por combinacion de cromosomas crm1+crm2
                    if(j<cnt_binaria){
                        crm.crm1=swap(crm.crm1,j,k);
                    }else{
                        crm.crm2=swap(crm.crm2,j-cnt_binaria,k);
                    }
                    crm = ajustes(crm); // calcula parámetros para la función objetivo
                    break;
                }
            }
        }
        sons[i] = crm;  // se incorpora arreglo de retornar cambios de cromosoma al adn? xD
    }
    return sons;
}


//*****************************************FIN PROCESO MUTACION2**************************************************************



//*****************************************INICIO PROCESO MUTACION3**************************************************************

cromosomas swap2(cromosomas sons,int j,int k){    //sons cromosoma a mutar,j=posicion fijada probabilisticamente a mutar, k=posicion aleatoria a mutar 
    string pl=bitset< 19 >( sons.crm1 ).to_string() + bitset< 19 >( sons.crm2 ).to_string(),bit="";
    int arr2[cnt_binaria*2];
    int arr[cnt_binaria];
    int aux;
    for(int i=0;i<cnt_binaria*2;i++) {
        bit = pl[i];
        arr2[i] = stoi(bit);
    }
    
    aux = arr2[j];      // intercambio de bits
    arr2[j] = arr2[k];
    arr2[k] = aux;
   
    for(int i=0;i<cnt_binaria;i++){
        arr[i] = arr2[i];
    }
    sons.crm1 = unbinary(arr);
    
    for(int i=cnt_binaria;i<cnt_binaria*2;i++){
        arr[cnt_binaria-i]= arr2[i];
    }
    sons.crm2 = unbinary(arr);
    
  
    return sons;

}



cromosomas* mutacion3(cromosomas* sons){
    Aleatorio *chg = new Aleatorio();
    //cambio realizado 26 - 07 - 2021
    //contempla búsqueda de cada individuo, busca bit a mutar en cromosoma completo, opera y continua con el siguiente
    
  int k=0;
  for(int i=0;i<cantidad;i++){
    if(chg->random(0,1)<pm){       //pregunta por individuo a mutar
        for(int j=0;j<cnt_binaria*2;j++){
            if(chg->random(0,1)<pm){       //pregunta cual bit muta y al realizar operación quebra ciclo
                k = (int)chg->random(1,cnt_binaria*2-1);    
                sons[i] = swap2(sons[i],j,k);
                sons[i] = ajustes(sons[i]);
                break;
            }
        }
    }
  }
  return sons;
} 


//*****************************************FIN PROCESO MUTACION3**************************************************************

string binary(int x){
    return bitset< 19 >( x ).to_string();
}

//*****************************************INICIO PROCESO CRUZAMIENTO***********************************************************

int corte_binario(int crm1, int x){
  string binario=binary(crm1),pl="";
  int bin_cuted[cnt_binaria];
  
  for(int i=0;i<cnt_binaria;i++){      //hago extracción particionada del cromosoma en la posición "x"    
    if(i<x){
        bin_cuted[i]=0;
    }else{
        pl = binario[i];
        bin_cuted[i] = stoi(pl);
    }
  }
  
  return unbinary(bin_cuted);    
}

cromosomas* cruce(cromosomas* sons){
  Aleatorio *chg = new Aleatorio();
  int cnt_out = round(cantidad*pc);      //cantidad de cromosomas a cruzar según la probabilididad asignada
  if(cnt_out%2!=0) cnt_out=cnt_out+1;    //determina si la selección será par o no, para poder obtener un cruzamiento pareado de todos los individuos
  int cruza [cnt_out],i;
  int aux1,aux2,rnd2,rnd_pos;
  float rnd;
  
  for(i=0;i<cnt_out;i++) cruza[i] = 0;       //medida temporal para que no evalue valores NULL
  
  //selecciona cromosomas para el cruzamiento según la probabilidad asignada, dentro de numeros aleatorios entre [0,1]
  aux2=0;
  for(i=0;i<cantidad;i++){
    rnd = chg->random(0,1);
    if(pc>rnd && aux2<cnt_out){
      cruza[aux2] = i;
      aux2++;
    }
  }
  aux2=0;
  
  
  for(i=0;i<cnt_out;i++){
    rnd2 = int(chg->random(0,cnt_out-1));            //escoje cromosoma aleatoriamente a cruzar, SE ARREGLA ALEATORIO POR ENCONTRAR NUMERO FUERA DEL ARRAY
    //rnd_pos = 15;                              //define desde que bit va a cruzar con el cromosoma seleccionado
    rnd_pos = int(chg->random(1,(cnt_binaria*2)-1));    //define aleatoreamente desde que bit va a cruzar con el cromosoma seleccionado
    
    if(cruza[i]!=cruza[rnd2] && cruza[i]>=0 && cruza[rnd2]>=0){    //evita la repetición en el cruce // produce segmentation fault usando cruza[i] cuando hay NULL
      if(cnt_binaria>rnd_pos){
        //cruzamiento a cromosoma x
        aux1 = corte_binario(sons[cruza[i]].crm1,rnd_pos);
        aux2 = corte_binario(sons[cruza[rnd2]].crm1,rnd_pos);
        
        sons[cruza[i]].crm1 = sons[cruza[i]].crm1 - aux1;
        sons[cruza[rnd2]].crm1 = sons[cruza[rnd2]].crm1 - aux2;
        
        sons[cruza[i]].crm1 = sons[cruza[i]].crm1 + aux2;
        sons[cruza[rnd2]].crm1 = sons[cruza[rnd2]].crm1 + aux1;
        
      }else{
        //cruzamiento a cromosoma y
        aux1 = corte_binario(sons[cruza[i]].crm2,rnd_pos-cnt_binaria);
        aux2 = corte_binario(sons[cruza[rnd2]].crm2,rnd_pos-cnt_binaria);
        
        sons[cruza[i]].crm2 = sons[cruza[i]].crm2 - aux1;
        sons[cruza[rnd2]].crm2 = sons[cruza[rnd2]].crm2 - aux2;
        
        sons[cruza[i]].crm2 = sons[cruza[i]].crm2 + aux2;
        sons[cruza[rnd2]].crm2 = sons[cruza[rnd2]].crm2 + aux1;
       
      }
      sons[cruza[i]] = ajustes(sons[cruza[i]]);     //ajusta los valores de x,y para evaluar en rastrigin
      cruza[i]=-1;    //Elimina los cromosomas cruzados del listado de seleccionados
      cruza[rnd2]=-1;  //
    }
  }
    return sons;
}

//*****************************************FIN PROCESO CRUZAMIENTO**************************************************************



//*****************************************MAIN**************************************************************
void display(cromosomas *k){
    for(int i=0;i<cantidad;i++){
        if((i%4)==0){
            cout<<"\n";
        }else{
            cout<<k[i].nm<<":"<<k[i].fit<<"\tx:"<<k[i].x<<"\ty:"<<k[i].y<<"\t\t";
        }
    }
    cout<<"\n\n\n";
}

void delay(int s){
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(s));
}

void loop(){
    int gen=0;
    cromosomas bestbuffer = cromosomas(0);
    
    cromosomas *padre = new cromosomas[cantidad]; 
    cromosomas *hijos = new cromosomas[cantidad];
    mesh_x(xx);
    mesh_y(yy);
    for(int i=0;i<cantidad;i++){
            padre[i] = cromosomas(i);
            padre[i].Eval();
            hijos[i] = cromosomas(i);
            hijos[i].Eval();
            bestbuffer = op_crm(padre[i],bestbuffer);
    }

    padre = probabilidades(padre);
    hijos = probabilidades(hijos);
    
    do{
        
        hijos = selecciona(bestbuffer, padre, hijos);   
        
        hijos = cruce(hijos);
        
        hijos = mutar_rr0(hijos); //revisar carga operacional
        
        //hijos = mutar_rr1(hijos); //revisar carga operacional
        
        //hijos = mutacion2(hijos);
        
        //hijos = mutacion3(hijos);
        
        reinicio();
        
        for(int i=0;i<cantidad;i++){
            padre[i].Eval();
            hijos[i].Eval();
            bestbuffer = op_crm(hijos[i],bestbuffer);      
        }
        
        padre = probabilidades(padre);
        hijos =probabilidades(hijos);
                
        padre = hijos;
        
        //******DESCOMENTAR PARA REVISAR DESPLIEGUE**********
        cout<<"Generacion: "<<gen;
        cout<<"\n\nBest: "<<bestbuffer.fit<<" x:"<<bestbuffer.x<<" y:"<<bestbuffer.y;     
        display(padre);
        gen++;
        //delay(1);                //permite hacer delay para mostrar paramtro en segundos
    }while(gbest>salida);
}

int main(int argc, char *argv[])        
{
    srand(time(NULL)); //cambia valores aleatorios cada vez q se ejecuta con otro tiempo pedido a memoria
    
    do{
        cout<<"\nIngrese la cantidad de individuos a evaluar: ";
        cin>>cantidad;
        if((pm*cantidad)>=cantidad){
            cout<<"\nIngremente cantidad, Prob mutación fijada: "<<pm;
        }
    }while(cantidad<5 && (pm*cantidad)>=cantidad);
    
    do{
        cout<<"\nIngrese criterio de parada < 1: ";
        cin>>salida;
    }while(salida>1.1);
    
    cnt_bin();
    
    loop();
    
    //system("PAUSE");
    return(0);
}





