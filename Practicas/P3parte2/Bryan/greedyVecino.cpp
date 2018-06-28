#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "creaMatriz.cpp"
using namespace std;

int greedyVecinos ( vector <vector <double> > &orden_ciudades, char* ruta ){
//primero se sacan los datos del archivo (coordenadas)
	vector <int> vx,vy;
	coordenadas(ruta,vx,vy);
//Luego se genera la matriz de distancias en ma
	vector <vector <int> > ma(vx.size(),vector<int>(vx.size()));
	matriz(ma,vx,vy);
// for que muestra las distancias en forma de matriz
 	/*for (int i=0; i<ma.size();i++){
	 for (int j=0; j<ma.size();j++){
	 cout << ma[i][j]<< " ";
	 }
	cout << endl;
	}
	*/
  
  //Mientras no hayamos hecho todos los recorridos (para ver quien tiene la distancia minima)
  //Candidatos: todas las ciudades 
  //Seleccionados: ciudades que ya hayamos seleccionado para este recorrido
  //while()//Función solución: cuando ya hayamos seleccionado todos los candidatos
  //Función factibilidad: este algoritmo es factible en cualquier situación ya que se puede ir de cualquier ciudad a cualquier otra
  //Función objetivo: la selección de ciudades en el orden que tengan la menor distancia
}

int main (int argc, char *argv[]){
  if ( argc < 2 ){
    cout << "Falta ruta de archivo de coordenadas de ciudades\n" << endl;
    exit(-1);
  }
  vector <vector <double> > pos_ciudades;
  greedyVecinos (pos_ciudades, argv[1]);
}
