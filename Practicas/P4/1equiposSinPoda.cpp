#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "generaEquipos.cpp"
using namespace std;

void imprimir_v (vector <int> v){
    for (int i = 0; i < v.size (); i++)
       cout << v[i] << "|";
}

int suma_sol (vector<int> v){
   int s=0;
   for (int i = 0; i < v.size (); i++)
       s+= v[i];
   return s;
}

void particion (vector <int> A, vector <int> B){

   if (suma_sol (A) == suma_sol (B)){
       cout << "Solucion con suma: "<< suma_sol(A)<<endl;
       cout << "A: ";
       imprimir_v (A);
       cout << "   B: ";
       imprimir_v (B);
       cout << endl;
   }
   else{
        for (int i= 0; i < A.size(); i++){
           if ( B.back () < A [i]){
               int aux = A[i];
               B.push_back (aux);
               A.erase (A.begin()+i);
               particion(A, B);
               A.insert (A.begin()+i,aux);
               B.pop_back();
            }
        }
   }
}

void particionA (vector <int> v ){
    if (suma_sol (v) % 2 == 0){
        vector <int> B(1, 0);
        particion (v, B);
    }
    else
        cout << "No existe un particion por ser suma impar" << endl;
}



int main(){
    vector <int> ma,mb;
    equipo(ma,13);
    mb.resize(ma.size());

 imprimir_v (ma);
    cout << endl;
    particion (ma,mb);
    //particionA (ma);
}
