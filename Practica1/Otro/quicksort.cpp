  
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
inline static 
void quicksort(int T[], int num_elem);
static void quicksort_lims(int T[], int inicial, int final);
inline static 
void insercion(int T[], int num_elem);
static void insercion_lims(int T[], int inicial, int final);
static void dividir_qs(int T[], int inicial, int final, int & pp);

inline static void insercion(int T[], int num_elem){
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final){
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_QS = 50;


inline void quicksort(int T[], int num_elem){
  quicksort_lims(T, 0, num_elem);
}

static void quicksort_lims(int T[], int inicial, int final){
  int k;
  if (final - inicial < UMBRAL_QS) {
    insercion_lims(T, inicial, final);
  } else {
    dividir_qs(T, inicial, final, k);
    quicksort_lims(T, inicial, k);
    quicksort_lims(T, k + 1, final);
  };
}


static void dividir_qs(int T[], int inicial, int final, int & pp){
  int pivote, aux;
  int k, l;

  pivote = T[inicial];
  k = inicial;
  l = final;
  do {
    k++;
  } while ((T[k] <= pivote) && (k < final-1));
  do {
    l--;
  } while (T[l] > pivote);
  while (k < l) {
    aux = T[k];
    T[k] = T[l];
    T[l] = aux;
    do k++; while (T[k] <= pivote);
    do l--; while (T[l] > pivote);
  };
  aux = T[inicial];
  T[inicial] = T[l];
  T[l] = aux;
  pp = l;
};




int main(int argc, char * argv[]){
  
    if (argc != 2){
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  int * T = new int[n];
  assert(T);

  srandom(time(0));

  for (int i = 0; i < n; i++){
      T[i] = random();
    };

  clock_t tantes,tdespues;
  double tiempo_transcurrido;
  int i;
  tantes=clock();
	quicksort(T, n);
  
  tdespues = clock();
  tiempo_transcurrido=((double)(tdespues-tantes)/(CLOCKS_PER_SEC));
  cout << n <<" "<< tiempo_transcurrido << endl;
  delete [] T;

  return 0;
};
 
