#ifndef __CREA_MATRIZ
#define __CREA_MATRIZ
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;


void coordenadas (char *ruta,vector <int> &valoresX,vector <int> &valoresY){
 vector <vector <double> > matriz;
  ifstream archivo1,archivo2;
  archivo1.open(ruta);

  string linea1, linea2, x1, x2, y1, y2;
  int coord_x1,coord_x2,coord_y1,coord_y2;
  string::iterator it1,it2;
getline(archivo1,linea1);//Primera línea donde pone: "DIMENSION ..."
//Primera linea para el while
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

	coord_x1 = atoi(x1.c_str());
	coord_y1 = atoi(y1.c_str());
valoresX.push_back(coord_x1);
valoresY.push_back(coord_y1);

	getline(archivo1,linea1); //siguiente linea
}
archivo1.close(); //cerramos archivo
}


void matriz (vector <vector <int> > &ma ,vector <int> &valoresX, vector <int> &valoresY){
for (int i=0; i<valoresX.size();i++){
	for (int j=0; j<valoresY.size();j++){
		if(i!=j)
		ma[i][j] = sqrt((valoresX[i]-valoresX[j])*(valoresX[i]-valoresX[j])+
					(valoresY[i]-valoresY[j])*(valoresY[i]-valoresY[j]));
		else
		ma[i][j]=0;
	}
}

}


#endif
