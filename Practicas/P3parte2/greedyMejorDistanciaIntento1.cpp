#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "creaMatriz.cpp"
using namespace std;

bool noCierraCircuito ( vector <int> &veces_usada_ciudad, int ciudad1, int ciudad2 ){
  bool esta_completo = true;
  int valor, numero_unos = 0;
  for ( int i = 0; i < veces_usada_ciudad.size(); i++ ){
    valor = veces_usada_ciudad[i];
    if ( i == ciudad1 || i == ciudad2 ) valor+=1;
    if ( valor < 2 ) esta_completo = false;
    if ( valor == 1 ) numero_unos++;
  }
  if ( esta_completo ) return true;
  else if ( numero_unos >= 2 ) return true;
  else return false;
}

void posicionaCiudades( vector <int> &siguiente_ciudad, int ciudad1, int ciudad2 ){
  if (siguiente_ciudad[ ciudad1 ] == -1 )
    siguiente_ciudad[ ciudad1 ] = ciudad2;
  else if (siguiente_ciudad[ ciudad2 ] == -1 )
    siguiente_ciudad[ ciudad2 ] = ciudad1;
  else{
    vector<int> guarda_orden;
    int ciudad_actual = ciudad1;
    int ciudad_inicial = ciudad1;
    guarda_orden.push_back(ciudad_actual);
    while ( siguiente_ciudad[ ciudad_actual ] != -1 ){
      guarda_orden.push_back(siguiente_ciudad[ ciudad_actual ]);
      ciudad_actual = siguiente_ciudad[ ciudad_actual ];
    }
    for ( int i = guarda_orden.size() - 1; i > 0; i--){
      siguiente_ciudad[guarda_orden[i]]=guarda_orden[i-1];
    }
    siguiente_ciudad[guarda_orden[0]]=ciudad_inicial;
    siguiente_ciudad[ ciudad1 ] = ciudad2;
  }
}

void reordenaPosiciones( vector <int> &siguiente_ciudad, vector <int> &posicion_ciudades, int ciudad_inicial ){
  int ciudad_actual = ciudad_inicial, contador = 0;
  while ( contador < siguiente_ciudad.size() ){
    posicion_ciudades.push_back(ciudad_actual);
    ciudad_actual = siguiente_ciudad[ciudad_actual];
    contador++;
  }
}

bool distanciaCogida( vector <vector <int> > &distancias_cogidas, int ciudad1, int ciudad2 ){
  bool esta_cogida = false;
  for (int i = 0; i < distancias_cogidas.size() && !esta_cogida; i++){
    if ( distancias_cogidas[i][0] == ciudad1 && distancias_cogidas[i][1] == ciudad2 )
      esta_cogida = true;
  }
  return esta_cogida;
}

int greedyVecinos ( vector <int> &orden_ciudades, char* ruta ){
//primero se sacan los datos del archivo (coordenadas)
  vector <int> vx,vy;
  coordenadas(ruta,vx,vy);
//Luego se genera la matriz de distancias en ma
  vector <vector <int> > distancias(vx.size(),vector<int>(vx.size()));
  matriz(distancias,vx,vy);
// for que muestra las distancias en forma de matriz
 	/*for (int i=0; i<distancias.size();i++){
	 for (int j=0; j<distancias.size();j++){
	 cout << distancias[i][j]<< " ";
	 }
	cout << endl;
	}*/
  int distancia_total = 0, menor_distancia,x_antigua,y_antigua,nueva_x,nueva_y;
  vector <int> siguiente_ciudad, veces_usada_ciudad;
  vector <vector <int> > distancias_cogidas;
  vector <int> ultima_distancia_cogida;

  for (int k = 0; k < distancias.size(); k++){
    siguiente_ciudad.push_back(-1);
    veces_usada_ciudad.push_back(0);
  }

  for (int k = 0; k < distancias.size(); k++){
    menor_distancia = 99999999;
    ultima_distancia_cogida.clear();
    for (int i = 0; i < distancias.size(); i++){
      for (int j = i+1; j < distancias.size(); j++){
        if (menor_distancia > distancias[i][j] && veces_usada_ciudad[i] < 2
          && veces_usada_ciudad[j] < 2 && noCierraCircuito(veces_usada_ciudad,i,j)
          && !distanciaCogida(distancias_cogidas,i,j)){
            //cout << "La distancia: "<< distancias[i][j] << ", entre las ciudades:  " << i << " y " << j << " es menor que la actual seleccionada: " << menor_distancia << endl;
            menor_distancia = distancias[i][j];
            nueva_x = i;
            nueva_y = j;
        }
      }
    }
    ultima_distancia_cogida.push_back(nueva_x);
    ultima_distancia_cogida.push_back(nueva_y);
    distancias_cogidas.push_back(ultima_distancia_cogida);
    //cout << "La menor de las distancias que se pueden coger es: "<< menor_distancia << "; entre las ciudades:  " << nueva_x << " y " << nueva_y << endl;
    veces_usada_ciudad[nueva_x]=veces_usada_ciudad[nueva_x]+1;
    veces_usada_ciudad[nueva_y]=veces_usada_ciudad[nueva_y]+1;
    posicionaCiudades(siguiente_ciudad,nueva_x,nueva_y);
    distancia_total+=menor_distancia;
    //cout << "La distancia acumulada actual es: " << distancia_total << endl;
  }
  reordenaPosiciones(siguiente_ciudad,orden_ciudades,nueva_y);
  return distancia_total;
}

int main (int argc, char *argv[]){
  if ( argc < 2 ){
    cout << "Falta ruta de archivo de coordenadas de ciudades\n" << endl;
    exit(-1);
  }
  vector <int> pos_ciudades;
  cout << "Distancia mínima: "<< greedyVecinos (pos_ciudades, argv[1])<<endl;
  for (int i = 0; i < pos_ciudades.size(); i++)
    cout << pos_ciudades[i]<<endl;
}
