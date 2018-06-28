#ifndef __GENERAEQUIPO
#define __GENERAEQUIPO
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;


void equipo (vector <int>&ma ,int tama){
int sumaParcial=0;
ma.resize(tama);
    for (int i=0; i<tama;i++){
		ma[i] = rand() % 10 + 1; //Random entre 1 y 10 (0 no se soporta por ser  un valor que no vale para el problema
		sumaParcial=sumaParcial+ma[i];
    }
    if(sumaParcial%2==1)
        ma[tama-1]++;
}

void equipoConSolucion(vector <int>&ma ,int tama){
int sumaParcial=0,t=0;

if(tama%2==1)
    t=tama-1;
else
    t=tama;

ma.resize(t);
    for (int i=0; i<t;i=i+2){
	ma[i] = rand() % 100 + 1;
        ma[i+1] = ma[i];

        sumaParcial=sumaParcial+ma[i]+ma[i+1];
    }
}

#endif
