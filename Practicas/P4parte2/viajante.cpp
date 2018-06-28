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

/****************************************************************************************/
/****************************** Define la clase Nodo ************************************/
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

/****************************************************************************************/
/****************************************************************************************/



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

  for ( int i = 0; i < ciudades.size() - 1; i++ ){
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
      for (int j = 0; j < distancias.size(); j++)
        if ( distancias[i][j] < distancia_minima && i != j )
          distancia_minima = distancias[i][j];
      suma_total += distancia_minima;
    }
  }
  return suma_total;
}

int viajante( vector <int> &orden_ciudades, char* ruta, int &nodos_expandidos, int &tamanio_cola, int &num_podas, int &n){
//primero se sacan los datos del archivo (coordenadas)
	vector <int> vx,vy;
	coordenadas(ruta,vx,vy);
//Luego se genera la matriz de distancias en ma
	vector <vector <int> > distancias(vx.size(),vector<int>(vx.size()));
	matriz(distancias,vx,vy);
	//cout <<"DISTANCIA:"<< distancias.size();
// for que muestra las distancias en forma de matriz
  /*for (int i=0; i<distancias.size();i++){
   for (int j=0; j<distancias.size();j++){
   cout << distancias[i][j]<< " ";
   }
  cout << endl;
  }*/

  n = distancias.size();
  nodos_expandidos = 0;
  tamanio_cola = 0;
  num_podas = 0;

  priority_queue <Nodo> pq;      //pq es una cola con prioridad de objetos de la clase Nodo

  int cota;
  int mejor_distancia_total = greedyMejorDistancia(distancias,orden_ciudades);//Calculamos cota utilizando el greedy de mejor distancia
  cout << "Cota superior inicial: " << mejor_distancia_total << "; Recorrido inicial: ";
  for(int i = 0; i < orden_ciudades.size(); i++)
    cout << orden_ciudades[i] << ", ";
  cout << endl;

  vector <int> ciudades;
  ciudades.push_back(0);
  Nodo e_nodo(calculaCota(distancias,ciudades),ciudades);
  pq.push(e_nodo);
  vector<int> aux_ciudades;

  while(!pq.empty()){
    //cout << "Entro en while" << endl;
    e_nodo=pq.top();//Elegimos el nodo con menor cota
    //cout << "El mejor candidato con cota " << e_nodo.cota() <<" es: ";
    aux_ciudades = e_nodo.ciudades();
    /*for(int i = 0; i < aux_ciudades.size(); i++)
      cout << aux_ciudades[i] << ", ";
    cout << endl;*/
    if(mejor_distancia_total<=e_nodo.cota()){//Podamos
      //cout << "Su cota es mayor a la cota superior: "<< mejor_distancia_total << ", así que se poda" << endl;
      pq.pop();
      num_podas++;
    }
    else{
      if(distancias.size() > e_nodo.ciudades().size()){//No es nodo hoja
        pq.pop();//Antes de expandir el e_nodo, lo sacamos de la cola
                 //(porque luego se meten nuevos nodos, y podría hacer pop de otro nodo que no es el e_nodo)
        aux_ciudades = e_nodo.ciudades();
        /*cout << "No es hoja, ni su cota excede a la cota superior (" << mejor_distancia_total << "), por lo que expandimos el nodo" << endl;
        for (int j = 0; j < aux_ciudades.size();j++)
          cout << aux_ciudades[j] << ", ";
        cout << endl <<"Expandimos las ciudades: "<<endl;*/
        for (int i = 0; i < distancias.size();i++){//Expandimos e_nodo
          if (!estaCiudad(e_nodo.ciudades(),i)){
            //cout << "Expandiendo nodos" << endl;
            ciudades = e_nodo.ciudades();
            ciudades.push_back(i);
            cota = calculaCota(distancias,ciudades);
            //cout << i << " con cota: " << cota << endl;
            Nodo aux(cota, ciudades);
            //cout << "Se añade con cota:"<<aux.cota();
            pq.push(aux);
          }
        }
        //cout << endl;
        nodos_expandidos++;
        if (tamanio_cola<pq.size()) tamanio_cola = pq.size();//Como se han introducido nuevos nodos, es en el
                                                             //único sitio donde puede haber aumentado el tamaño de la cola
      }
      else{//Es nodo hoja, luego miramos si es mejor recorrido que el antiguo y actualizamos cota
        //cout << "Es nodo hoja" << endl;
        if( mejor_distancia_total > e_nodo.cota()){
          //cout << "Es mejor distancia. Antigua cota superior: "<<mejor_distancia_total<<"; nueva cota superior: "<<e_nodo.cota() << endl;
          mejor_distancia_total = e_nodo.cota();
          orden_ciudades = e_nodo.ciudades();
        }
        pq.pop();//Sea o no el mejor recorrido, lo sacamos de la cola
      }
    }
  }
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
  distancia_minima = viajante (pos_ciudades, argv[1], nodos_expandidos, tamanio_cola, num_podas, n);
  tdespues = clock();
  cout << "Distancia mínima: " << distancia_minima << endl;
  cout << "Nº de nodos expandidos: " << nodos_expandidos << endl;
  cout << "Tamanio máximo de la cola con prioridad de nodos vivos: " << tamanio_cola << endl;
  cout << "Nº de veces podadas: " << num_podas << endl;
  cout << "Nº ciudades del archivo de entrada: " << n << endl;
  cout << "Tiempo empleado en algoritmo: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
  for (int i = 0; i < pos_ciudades.size(); i++)
    cout << pos_ciudades[i]<<endl;
  //cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
}
