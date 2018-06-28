#include <iostream>
using namespace std;
#include <ctime>
int fibo(int n){
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(){
  clock_t tantes,tdespues;
  double tiempo_transcurrido;
  int f;
  const int NUM_VECES=1000;
  int i;

	tantes=clock();
	for (i=0; i<NUM_VECES;i++){
		tantes=clock();
		f = fibo(i);
		tdespues = clock();
		tiempo_transcurrido=((double)(tdespues-tantes)/(CLOCKS_PER_SEC));
		cout << i <<" "<< tiempo_transcurrido << endl;
	}
}
 
