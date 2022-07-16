//
// Created by gino on 16/6/21.
//

#ifndef MAIN_CPP_BUSQUEDAAMPLITUD_TPP
#define MAIN_CPP_BUSQUEDAAMPLITUD_TPP
#include <iostream>

#include "Cola.h"

using namespace std;

#define INFI  9000
//#define MAXNODOS  4
#define no_visitado 0
#define visitado 1
#define MAX 8



class busqAmplitud {
public:
    int c = -1;
    int **caminosH;
    int cantV;
    void BEA(bool **&, int**&, int marca[], vector<coordenada>);
    void guardarReg(int, int);
    busqAmplitud( int cantV) {
        this->cantV= cantV;
        caminosH = (int**)calloc(cantV, sizeof (int*));
    // en cada posicion del "array", reservo memoria para sus columnas
        for (int i = 0; i < cantV; i++)
            caminosH[i] = (int*)calloc(cantV, sizeof(int));

        for (int i = 0; i < cantV; i++) {
            for (int j = 0; j < cantV; j++) {
                caminosH[i][j] = -1;
            }
        }
    };
};
#endif //MAIN_CPP_BUSQUEDAAMPLITUD_TPP
