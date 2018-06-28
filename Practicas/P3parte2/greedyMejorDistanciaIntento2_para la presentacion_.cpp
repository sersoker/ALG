#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "creaMatriz.cpp"
using namespace std;

bool esFactible ( vector <vector <int> > &ciudades_anexas, vector <int> &veces_usada_ciudad, int ciudad1, int ciudad2 ){
  if (veces_usada_ciudad[ciudad1] == 2 || veces_usada_ciudad[ciudad2] == 2) return false;

  bool bucle = false, encontrado, para = false;
  int ciudad_actual = ciudad2, siguiente_ciudad, antigua_ciudad = ciudad1;//Según como tenemos hecho el algoritmo, ciudad1 siempre es mayor que ciudad2
  for ( int i = 0; i < ciudades_anexas.size()-2&&!bucle&&!para; i++ ){//Esto solo nos sirve de tope para, en caso de que fuera la última distancia que puede coger, se termine el bucle al llegar a distancias.size()-1
    encontrado = false;
    for (int j = 0; j < ciudades_anexas.size() && !bucle && !encontrado&&!para; j++){
      if (ciudades_anexas[ciudad_actual][j] == 1 && j!=antigua_ciudad){
        if (j == ciudad1) bucle = true;//Vuelve a pasar por ciudad1, por lo que hay bucle
        else{//Hemos encontrado la siguiente ciudad a la que movernos
          encontrado = true;
          siguiente_ciudad = j;
        }
      }
    }
    if( !encontrado ) para = true;//Si no hemos encontrado una ciudad a la que movernos, significa que hemos llegado al final del recorrido y no ha habido bucle
    else{
      antigua_ciudad = ciudad_actual;//Avanzamos a la
      ciudad_actual = siguiente_ciudad;//siguiente ciudad
    }
  }
  return !bucle;
}

void reordenaPosiciones( vector <vector <int> > &ciudades_anexas, vector <int> &posicion_ciudades ){
  int ciudad_actual = 0, siguiente_ciudad, antigua_ciudad = 0;
  bool encontrado;
  for ( int i = 0; i < ciudades_anexas.size(); i++ ){
    encontrado = false;
    for (int j = 0; j < ciudades_anexas.size() && !encontrado; j++){
      if (ciudades_anexas[ciudad_actual][j] == 1 && j!=antigua_ciudad){
        encontrado = true;
        siguiente_ciudad = j;
      }
    }
    antigua_ciudad = ciudad_actual;
    ciudad_actual = siguiente_ciudad;
    posicion_ciudades.push_back(ciudad_actual);
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

  //Declaramos variables
  int distancia_total = 0, menor_distancia,x_antigua,y_antigua,nueva_x,nueva_y;
  vector <int> siguiente_ciudad, veces_usada_ciudad;
  vector <vector <int> > distancias_cogidas;
  vector <int> ultima_distancia_cogida;
  vector <vector <int> > ciudades_anexas;
  vector<int> vector_ciudades_anexas;

  //Inicializamos vectores y matrices
  for (int i = 0; i < distancias.size(); i++)
    vector_ciudades_anexas.push_back(0);
  for (int k = 0; k < distancias.size(); k++){
    veces_usada_ciudad.push_back(0);
    ciudades_anexas.push_back(vector_ciudades_anexas);
  }

  //Conseguimos la matriz con todos los caminos a tomar
  for (int k = 0; k < distancias.size(); k++){
    menor_distancia = 99999999;
    ultima_distancia_cogida.clear();
    //Doble bucle para elegir mejor distancia
    for (int i = 0; i < distancias.size(); i++){
      for (int j = i+1; j < distancias.size(); j++){
        if (menor_distancia > distancias[i][j] && esFactible(ciudades_anexas,veces_usada_ciudad,i,j) && !distanciaCogida(distancias_cogidas,i,j)){
            menor_distancia = distancias[i][j];
            nueva_x = i;
            nueva_y = j;
        }
      }
    }
    //Añadimos a distancias_cogidas las nuevas dos ciudades anexas (para luego comprobar si las futuras distancias a elegir
    //ya la habiamos cogido o no)
    ultima_distancia_cogida.push_back(nueva_x);
    ultima_distancia_cogida.push_back(nueva_y);
    distancias_cogidas.push_back(ultima_distancia_cogida);

    veces_usada_ciudad[nueva_x]=veces_usada_ciudad[nueva_x]+1;
    veces_usada_ciudad[nueva_y]=veces_usada_ciudad[nueva_y]+1;
    //Indicamos en la matriz ciudades_anexas el nuevo enlace entre estas dos ciudades
    ciudades_anexas[nueva_x][nueva_y]=ciudades_anexas[nueva_x][nueva_y]+1;
    ciudades_anexas[nueva_y][nueva_x]=ciudades_anexas[nueva_y][nueva_x]+1;
    distancia_total+=menor_distancia;
  }
 
  //Creamos la ruta en el vector orden_ciudades gracias a la matriz ciudades_anexas
  reordenaPosiciones(ciudades_anexas,orden_ciudades);
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
