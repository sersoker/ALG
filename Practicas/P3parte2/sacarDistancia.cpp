#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

int main (int argc, char *argv[]){
  if ( argc < 2 ){
    cout << "Falta ruta de archivo de coordenadas de ciudades\n" << endl;
    exit(-1);
  }
  int distancia_total = 0, x_antigua,y_antigua,x_actual,y_actual; 

 vector <vector <double> > matriz;
  ifstream archivo1,archivo2;
  archivo1.open(argv[1]);

  string linea1, linea2, x1, x2, y1, y2;
  int coord_x1,coord_x2,coord_y1,coord_y2;
  string::iterator it1,it2;
getline(archivo1,linea1);//Primera línea donde pone: "DIMENSION ..."
//Primera linea para el while
getline(archivo1,linea1);
// cout << linea1 <<endl;
x1.clear();
y1.clear();
//Iterador al princpio de la linea
it1=linea1.begin();
//Conseguimos las coordenadas
while (*it1==' ') it1++; //Nos saltamos los espacios iniciales si tiene
while (*it1!=' ') it1++; //Ahora nos saltamos en numero de ciudad
while (*it1==' ') it1++; //Y de nuevo los espacios
while (*it1!=' '){       //Coordenada x
  x1 += (*it1);
  it1++;
}
while (*it1==' ') it1++;
while (it1!=linea1.end()){//Coordenada y
  y1 += (*it1);
  it1++;
}
x_antigua = atoi(x1.c_str());//ESTO ES LO IMPORTANTE DE AQUI
//cout << "La coordenada x de la ciudad inicial es: "<<x_antigua<<endl;
y_antigua = atoi(y1.c_str());
//cout << "La coordenada x de la ciudad inicial es: "<<y_antigua<<endl;

getline(archivo1,linea1);
while (archivo1.good()){

	   // cout << linea1 <<endl;
	    x1.clear();
	    y1.clear();
	//Iterador al princpio de la linea
	it1=linea1.begin();
	//Conseguimos las coordenadas
	    while (*it1==' ') it1++; //Nos saltamos los espacios iniciales si tiene
	    while (*it1!=' ') it1++; //Ahora nos saltamos en numero de ciudad
	    while (*it1==' ') it1++; //Y de nuevo los espacios
	    while (*it1!=' '){       //Coordenada x
	      x1 += (*it1);
	      it1++;
	    }
	    while (*it1==' ') it1++;
	    while (it1!=linea1.end()){//Coordenada y
	      y1 += (*it1);
	      it1++;
	    }

	x_actual = atoi(x1.c_str());
        //cout << "La coordenada x de la ciudad actual es: "<<x_actual<<endl;
	y_actual = atoi(y1.c_str());
        //cout << "La coordenada y de la ciudad actual es: "<<y_actual<<endl;
        distancia_total += sqrt((x_actual-x_antigua)*(x_actual-x_antigua)+(y_actual-y_antigua)*(y_actual-y_antigua));
        //cout << "La distancia entre las dos ciudades es: "<<sqrt((x_actual-x_antigua)*(x_actual-x_antigua)+
        //(y_actual-y_antigua)*(y_actual- y_antigua))<<endl;
        //cout << "La distancia máxima actual es: "<<distancia_total<<endl;
        x_antigua = x_actual;
        y_antigua = y_actual;

	getline(archivo1,linea1); //siguiente linea
}
archivo1.close(); //cerramos archivo

cout << argv[1]<<" "<<distancia_total<<endl;
}
