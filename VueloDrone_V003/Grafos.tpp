//
// Created by gino on 14/6/21.
//

#ifndef VUELODRONE_V00_GRAFOS_TPP
#define VUELODRONE_V00_GRAFOS_TPP

#include <iostream>
#include <cmath>
#include <vector>
#include "Segmento.h"

using namespace std;

class Grafos{
private:
        int tamanioMaleza(bool**v, int size, int i, int j);
        void setAristas(vector<coordenada>);
        void coordObs(bool**&, int, int, int);
        vector<coordenada> pVert;
        vector<segmento> rAristas;
        vector<segmento> rObstaculo;
public:
        Grafos(){};
        bool** crearMatriz(int n);
        void setGrafo(string fila, bool**&m, bool**&o,bool**&v,bool**&vaux, int f, int n);
        void buscarVertices(bool**&, bool**&, vector<coordenada>&, int);
        void printGrafo(bool** m, int f);
        void buscarObstaculos(bool** o, int size);
        void printVObstaculos();

        void getMatrizAdy(vector<coordenada>, bool**&);
        friend bool operator==(coordenada, coordenada);
        friend bool operator|(segmento , segmento); // para preguntar si se interfieren dos segmentos
        friend bool operator-(segmento , segmento); //para calcular si son segmentos colineales
        friend int operator>>(segmento , coordenada); //req para interferencia (pregunta como es el producto cruz)
};

#endif //VUELODRONE_V00_GRAFOS_TPP
