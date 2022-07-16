//
// Created by gino on 14/6/21.
//

#ifndef VUELODRONE_V00_CICLO_HAMILTON_TPP
#define VUELODRONE_V00_CICLO_HAMILTON_TPP
#include <iostream>
#include "vector"
#include "Segmento.h"

using namespace std;

class Hamilton{
private:
    int a =0;
    double acumm= 0;
    bool b = true;
    int nvert = 0; // Numero de vertices en el grafo
    vector<int> caminoAux;
    bool **grafo;

    bool caminoViable(int v, bool **grafico, vector<int> camino, int pos);
    bool hamiltonAux(bool **grafico, vector<int> &camino, int pos);
    void Distancia(vector<int>, vector<coordenada>);
public:
    Hamilton();
    friend double operator&(coordenada , coordenada); //recibe la distancia entre dos puntos (coordenadas)
    bool cicloHamilton(bool **grafico,vector<coordenada>, vector<int>);
    void imprimirSolucion(vector<int> camino);
    double calcularDistancia(vector<int>, vector<coordenada>);
    void MejorCamino();
};

#endif //VUELODRONE_V00_CICLO_HAMILTON_TPP
