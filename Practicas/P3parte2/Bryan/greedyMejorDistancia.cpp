#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "creaMatriz.cpp"
using namespace std;

bool buscaCiudad(vector <int> &pos_ciudades, int indice){
  for (int i = 0; i < pos_ciudades.size(); i++){
    if(pos_ciudades[i]==indice)
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

bool comprueba2(vector <int> usadosx,int x,int y){

usadosx[x]++;
usadosx[y]++;
for(int i=0;i<usadosx.size();i++)
	if(usadosx[i]==1) return true;

}

void buscamenor(vector <vector <int> > &matriz,vector <int> &usadosx,int &x,int &y,vector <vector <int> > &matrizCogidos){
	int menorActual=999999;
	int xa,ya;
	for(int i=1;i<matriz.size();i++){
		for(int j=0;j<matriz.size();j++){
			if(i>j&&matriz[i][j]<menorActual&&usadosx[i]<2&&usadosx[j]<2&&comprueba2(usadosx,i,j)){
				if(matrizCogidos[i][j]!=1){
					menorActual=matriz[i][j];
					xa=i; ya=j;
				}
			}
		}
	}
	x=xa; y=ya;
	usadosx[x]++;
	usadosx[y]++;
	matrizCogidos[x][y]=1;
	matrizCogidos[y][x]=1;

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

for(int i=0;i<usadosx.size()-1;i++){
	buscamenor(distancias,usadosx,x,y,cogidos);
	cout << x <<" "<< y << endl;
}

cout << "listaUsados"<<endl;
	for(int i=0;i<usadosx.size();i++)
		cout << usadosx[i];
cout << endl;

int a=0,b=0;
 	for (int i=0; i<usadosx.size();i++){
	 	if (a==0&&usadosx[i]==1)
	 		a=i;
	 	if(a!=0&&usadosx[i]==1)
	 		b=i;
	 }
cogidos[a][b]=1;
cogidos[b][a]=1;

// for que muestra la matriz del camino
 	for (int i=0; i<cogidos.size();i++){
	 for (int j=0; j<cogidos.size();j++){
	 cout << cogidos[j][i]<< " ";
	 }
	cout << endl;
	}

int i=0;
int j=0;
while(orden_ciudades.size()<distancias.size()){
	if(cogidos[i][j]!=1){
          j++;
    }
    else {
    	if(buscaCiudad(orden_ciudades,j)){
          	orden_ciudades.push_back(i);
          	i=j;
        	j=0;
    	}
    	else
    		j++;
    }
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
