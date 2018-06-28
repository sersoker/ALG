#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "creaMatriz.cpp"
using namespace std;

bool buscaCiudad(vector <int> &ciudades, int indice){
  for (int i = 0; i < ciudades.size(); i++){
    if(ciudades[i]==indice)
      return false;
  }
  return true;
}

int calculatama(vector <int> &pos_ciudades,vector <vector <int> > &matriz){
	int acumulado=0;
	for(int i=0;i<pos_ciudades.size()-1;i++)
		acumulado=acumulado+matriz[pos_ciudades[i]][pos_ciudades[i+1]];
	acumulado=acumulado+matriz[pos_ciudades[0]][pos_ciudades[pos_ciudades.size()-1]];
return acumulado;
}

void buscamenor(vector <vector <int> > &matriz,vector <int> &usadosx,int &x,int &y){
	int menorActual=999999;
	int xa,ya;
	for(int i=1;i<matriz.size();i++){
		for(int j=0;j<matriz.size();j++){
			if(i>j&&matriz[i][j]<menorActual){
					menorActual=matriz[i][j];
					xa=i; ya=j;
				}
			}
		}
	
	x=xa; y=ya;
}

void buscaSiguiente(int &x,int &y,vector <int> &orden_ciudades,vector <vector <int> > &matriz){
int menorActual=999999;
int xa,ya;
		for(int j=0;j<matriz.size();j++){
			if(matriz[y][j]<menorActual&&buscaCiudad(orden_ciudades,j)){
					menorActual=matriz[y][j];
					xa=j; ya=y;
				}
			}
	
x=xa; y=ya;

}


vector <int> vx,vy;

int greedyVecinos ( vector <int> &orden_ciudades, char* ruta ){
//primero se sacan los datos del archivo (coordenadas)
  coordenadas(ruta,vx,vy);
//Luego se genera la matriz de distancias en ma
  vector <vector <int> > distancias(vx.size(),vector<int>(vx.size()));
  matriz(distancias,vx,vy);
// for que muestra las distancias en forma de matriz
 	for (int i=0; i<distancias.size();i++){
	 for (int j=0; j<distancias.size();j++){
	 cout << distancias[i][j]<< " ";
	 }
	cout << endl;
	}

	int tama =vx.size();
	int x, y;
	vector <int> usadosx (tama,0);
    vector <vector <int> > cogidos(vx.size(),vector<int>(vx.size(),0));
	cout <<"tama:"<< tama<<endl;

	buscamenor(distancias,usadosx,x,y);
		cout << x <<" "<< y << endl;
		orden_ciudades.push_back(x);
	while(orden_ciudades.size()<distancias.size()){
		x=0;
		buscaSiguiente(x,y,orden_ciudades,distancias);
		orden_ciudades.push_back(x);

	}

return calculatama(orden_ciudades,distancias);
}

int main (int argc, char *argv[]){
  if ( argc < 2 ){
    cout << "Falta ruta de archivo de coordenadas de ciudades\n" << endl;
    exit(-1);
  }
  vector <int> pos_ciudades;
  cout << "Distancia mínima: "<< greedyVecinos (pos_ciudades, argv[1])<<endl;
  for (int i = 0; i < pos_ciudades.size(); i++)
    cout << pos_ciudades[i]<< " "<<vx[pos_ciudades[i]] << " " << vy[pos_ciudades[i]]<<endl;
}
