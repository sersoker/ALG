#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

clock_t tantes, tdespues;

//generador de ejemplos para el problema de la serie unimodal de números. Se genera un índice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese índice, a los índices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los índices mayores que p se le asignan valores en orden decreciente (n-2, n-1,...,p

int Unimodal(int v[], int ini, int fin){
  int max = ini;
  for (int i = ini + 1; i <= fin; i++){
    if ( v[i] > v[max]){//Guardamos la posicion
      max = i;
      //cout << "Posicion " << i << " valor " << v[i] <<" avanzamos" << endl;
    }
    else{//Ya ha encontrado el pico, no hace falta seguir
      //cout << "Posicion " << max << " es el pico" << endl;
      return max;
    }
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

  int * T = new int[n];
  assert(T);

srand(time(0));
double u=uniforme();
int p=1+(int)((n-2)*u);
T[p]=n-1;
for (int i=0; i<p; i++) T[i]=i;
for (int i=p+1; i<n; i++) T[i]=n-1-i+p;

//for (int j=0; j<n; j++) {cout << T[j] << " ";}

tantes = clock();
int pos_pico = Unimodal ( T, 0, n-1 );
tdespues = clock();

cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
//cout << "Pico en posición: " << pos_pico << "; Valor: " << T[pos_pico]<< endl;

} 
