#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "generaEquipos.cpp"
#include <ctime>

using namespace std;

clock_t tantes, tdespues;
int num_veces = 30;

vector <vector <int> > soluciones;

//Imprime los números actuales añadidos al equipo del índice pasado (los que no estén, se imprime un 0)
void imprimir_v (vector<int> &mv,vector <int> &v, int indice){
    for (int i = 0; i < v.size (); i++){
        if(v[i]==indice)
            cout << mv[i] << "|";
        else
            cout << "0|";
    }
}

//Imprime todas las soluciones encontradas
void imprimeSoluciones(vector <int> &mv){
  for ( int i = 0; i < soluciones.size(); i++ ){
    cout << "A: ";
    imprimir_v(mv,soluciones[i],1);
    cout << "; B: ";
    imprimir_v(mv,soluciones[i],2);
    cout << endl;
  }
}

//Suma los números metidos actualmente en el equipo que se le indique con índice
int suma_sol(vector<int> &mv,vector<int> &v, int indice){
   int s=0;
   for (int i = 0; i < v.size (); i++){
        if(v[i]==indice)
            s+=mv[i];
    }
    if(s!=0)
       return s;
    else
       return -1;
}


//Devuelve si todos los números han sido ubicados en un equipo, 
//y la suma de los números de los dos equipos es la misma
bool esSolucion(vector<int> &mv,vector<int> &v){
    if(mv.size()>v.size())
        return false;
    int s=0;
    if (suma_sol (mv,v,1) == suma_sol (mv,v,2))
        s=suma_sol (mv,v,1);

    //cout << "Suma:"<< s << endl;
    if(s>0)
        return true;

    else
        return false;

}

void particion(vector <int> &MV,vector <int> &S){
        //cout << "sizes "<< S.size() << " "<<MV.size() <<endl;

        S.push_back(1);
        //cout << "sizes "<< S.size() << " "<<MV.size() <<endl;
        if(S.size()<MV.size())
            particion(MV,S);
        if(esSolucion(MV,S)){
            soluciones.push_back(S);
        }
        S.pop_back();
        S.push_back(2);

        if(S.size()<MV.size())
            particion(MV,S);

        if(esSolucion(MV,S)){
            soluciones.push_back(S);
        }
        S.pop_back();

}

int main(int argc, char * argv[]){
  if (argc != 2){
    cerr << "Formato " << argv[0] << " <num_elem>" << endl;
    return -1;
  }
  int n = atoi(argv[1]);
  vector <int> mv,ma,m1;
  equipo(mv,n);
  //ma.resize(mv.size());
  m1.resize(mv.size(),1);

  //cout << "Vector inicial: ";
  //imprimir_v (mv,m1,1); cout << endl;
  //cout << "Soluciones: " << endl;
  tantes = clock();
  particion (mv,ma);
  tdespues = clock();

  //imprimeSoluciones(mv);
  //cout << "Tamaño: " << n << "; tiempo: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
  cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
}
