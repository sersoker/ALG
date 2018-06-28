#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "creaMatriz.cpp"
#include <queue>
#include <ctime>
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


int greedyMejorDistancia ( vector <vector <int> > &distancias, vector <int> &orden_ciudades){

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

/* Define la clase Nodo */
class Nodo{
  public:
    Nodo() {};                                      //Constructor por defecto
    Nodo(int x, vector<int> y) { c = x; ciu = y; }    //Constructor
    bool operator<(const Nodo&) const;              //Sobrecarga operador <

    int cota() const { return c; }             //accessor methods
    vector<int> ciudades() const { return ciu; }

  private:
    int c;
    vector<int> ciu;                                 //Vector de ciudades (recorrido: camino actual)
};

/* Sobrecarga del operador <  para que la cola con prioridad sepa comparar dos objetos de la clase Nodo*/
bool Nodo::operator<(const Nodo& derecha) const{
  return c>derecha.c;//ESTA CAMBIADO PARA QUE NOS ELIJA EL DE MENOR PRIORIDAD
}

/*Indica si el numero de una ciudad esta en el recorrido elegido actualmente*/
bool estaCiudad(vector <int> pos_ciudades, int indice){
  for (int i = 0; i < pos_ciudades.size(); i++){
    if(pos_ciudades[i]==indice)
      return true;
  }
  return false;
}

int calculaCota( vector <vector <int> > &distancias, vector <int> ciudades ){
  int suma_total = 0;
  int distancia_minima;
  if ( distancias.size() == ciudades.size() ){//Ya están todas las ciudades. Calculamos la distancia total del circuito
    for ( int i = 0; i < ciudades.size() - 1; i++ ){
      suma_total += distancias[ciudades[i]][ciudades[i+1]];
    }
    suma_total += distancias[ciudades[0]][ciudades[ciudades.size()-1]];//Para cerrar el circuito entre la primera y última ciudad
  }
  else{//Todavía quedan ciudades por meter en el recorrido
    for ( int i = 0; i < ciudades.size() - 1; i++ ){//Recorremos las distancias entre las ciudades ya tomadas
      suma_total += distancias[ciudades[i]][ciudades[i+1]];
    }

    distancia_minima = 99999999;
    for (int i = 0; i < distancias.size(); i++)
      if ( distancias[ciudades[ciudades.size()-1]][i] < distancia_minima && ciudades[ciudades.size()-1]!=i )//Este trozo es para afinar más la cota.
                                                                                                        //Si no, faltaría tomar una distancia para completar el circuito
        distancia_minima = distancias[ciudades[ciudades.size()-1]][i];

    suma_total += distancia_minima;

    for (int i = 0; i < distancias.size(); i++){//Bucle para las ciudades no están en el recorrido actual
      if (!estaCiudad(ciudades,i)){
        distancia_minima = 99999999;
        for (int j = 0; j < distancias.size(); j++)//Para cada ciudad no incluída en el circuito actual
          if ( distancias[i][j] < distancia_minima && i != j )//Se elige la distancia menor para esa ciudad y se añade a la cota
            distancia_minima = distancias[i][j];
        suma_total += distancia_minima;
      }
    }
  }
  return suma_total;
}

//Algoritmo recursivo de backtracking con poda
void backtracking( vector <vector <int> > &distancias, vector <int> &orden_ciudades, int &cota_superior, vector <int> &recorrido_actual, int &nodos_expandidos, int &num_podas ){
  /*cout << "Recorrido actual: " ;
  for (int i = 0; i < recorrido_actual.size(); i++)
    cout << recorrido_actual[i] << ", ";
  cout << endl;*/
  int cota_optimista = calculaCota( distancias, recorrido_actual );
  if (recorrido_actual.size() < distancias.size()){//No es nodo hoja
    //cout << "No es nodo hoja. ";
    if ( cota_optimista < cota_superior ){ //Si fuera mayor o igual, se podaría (pero podar en este caso es no seguir la recursividad por ahí, así que no se hace nada)
      //cout << "Su cota es de " << cota_optimista << ", menor que la cota superior ("<< cota_superior <<"), por lo que lo expandimos"<<endl;
      nodos_expandidos++;
      for (int i = 0; i < distancias.size(); i++ )
        if ( !estaCiudad( recorrido_actual, i ) ){
          recorrido_actual.push_back(i);
          backtracking( distancias, orden_ciudades, cota_superior, recorrido_actual, nodos_expandidos, num_podas );
          recorrido_actual.pop_back();
        }
      //cout << endl;
    }
    else{ 
      //cout << "Su cota es de " << cota_optimista << ", mayor o igual que la cota superior ("<< cota_superior <<"), por lo que podamos"<<endl;
      num_podas++;
    }
  }
  else{//Es nodo hoja
    //cout << "Es nodo hoja. ";
    if ( cota_optimista < cota_superior ){
      //cout << "Su cota es de "<< cota_optimista << ", menor que la cota superior ("<< cota_superior <<"), por lo que cambiamos de cota superior y de camino"<<endl;
      cota_superior = cota_optimista;
      orden_ciudades = recorrido_actual;
    }
    //else cout << "Su cota es de "<< cota_optimista << ", mayor o igual que la cota superior ("<< cota_superior <<"), por lo que desechamos este camino"<<endl;
  }
}

int viajante( vector <int> &orden_ciudades, char* ruta, int &nodos_expandidos, int &num_podas, int &n ){
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

  n = distancias.size();
  nodos_expandidos = 0;
  num_podas = 0;

  int cota;
  int mejor_distancia_total = greedyMejorDistancia(distancias,orden_ciudades);//Calculamos cota utilizando el greedy de mejor distancia
  vector <int> recorrido_actual;
  recorrido_actual.push_back(0);

  backtracking(distancias, orden_ciudades, mejor_distancia_total, recorrido_actual, nodos_expandidos, num_podas);

  return mejor_distancia_total;
}

int main (int argc, char *argv[]){
  if ( argc < 2 ){
    cout << "Falta ruta de archivo de coordenadas de ciudades\n" << endl;
    exit(-1);
  }
  clock_t tantes, tdespues;
  int n, distancia_minima, nodos_expandidos, tamanio_cola, num_podas;
  vector <int> pos_ciudades;
  tantes = clock();
  distancia_minima = viajante (pos_ciudades, argv[1], nodos_expandidos, num_podas, n);
  tdespues = clock();

  cout << "Distancia total mínima: "<< distancia_minima << endl;
  cout << "Nº de nodos expandidos: " << nodos_expandidos << endl;
  cout << "Nº de veces podadas: " << num_podas << endl;
  cout << "Nº ciudades del archivo de entrada: " << n << endl;
  cout << "Tiempo en ejecutar algoritmo: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
  cout << "Recorrido: " <<endl;
  for (int i = 0; i < pos_ciudades.size(); i++)
    cout << pos_ciudades[i]<<endl;
  //cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
}
