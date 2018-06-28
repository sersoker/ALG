#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>

clock_t tantes, tdespues;

//generador de ejemplos para el problema de la serie unimodal de números. Se genera un índice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese índice, a los índices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los índices mayores que p se le asignan valores en orden decreciente (n-2, n-1,...,p

int posMax(vector<int> &v,int pos1, int pos2){
  if(v[pos1]>v[pos2])
    return pos1;
  else
    return pos2;
}

int Unimodal(vector<int> &v, int ini, int fin){
  if (ini == fin){//Caso base 1. Sólo tenemos 1 elemento
    return ini;
  }
  else if (ini+1 == fin){//Caso base 2. Tenemos 2 elementos
    return posMax(v,ini,fin);
  }
  else{//Tenemos más de dos elemento
    int medio = (fin+ini)/2, cuarto,primera_pos,segunda_pos, maximo;

    if(v[medio]<v[medio-1]){//El pico está a la izquierda de medio
      cuarto = (medio+ini)/2;//Si tenemos 3 elementos, cuarto == ini 
      primera_pos = Unimodal(v,ini,cuarto);
      segunda_pos = Unimodal(v,cuarto+1,medio);
    }
    else if(v[medio]<v[medio+1]){//El pico está a la derecha de medio
      cuarto = (fin+medio)/2;
      primera_pos = Unimodal(v,medio,cuarto);
      segunda_pos = Unimodal(v,cuarto+1,fin);
    }
    else//Caso base 3.El pico es medio
      return medio;
   
    maximo = posMax(v,primera_pos,segunda_pos);

    return maximo;
  }
}

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
double u;
  u = (double) rand();
  u = u/(double)(RAND_MAX+1.0);
 return u;
}

int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  vector<int> T;
	T.reserve(n);
  //assert(T);

srand(time(0));
double u=uniforme();
int p=1+(int)((n-2)*u);
T[p]=n-1;
for (int i=0; i<p; i++) T[i]=i;
for (int i=p+1; i<n; i++) T[i]=n-1-i+p;

//for (int j=0; j<n; j++) {cout << T[j] << " ";}

tantes = clock();
int pos_pico = Unimodal (T, 0, n-1 );
tdespues = clock();

cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
//cout << "Pico en posición: " << pos_pico << "; Valor: " << T[pos_pico]<< endl;

} 
