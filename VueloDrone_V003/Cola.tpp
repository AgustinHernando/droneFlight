//
// Created by gino on 16/6/21.
//

#ifndef MAIN_CPP_COLA_TPP
#define MAIN_CPP_COLA_TPP
#include <iostream>

using namespace std;

#define no_visitado 0
#define visitado 1
#define MAX 150

using namespace std;
// almacena MAX-1 elementos
// cola circular
class Cola{
private:
    int Q[MAX];
    int pi,pf;
public:
    Cola(void){pi=0;pf=MAX-1;};
    //~Cola(void);
    int tope(){return Q[pi];};
    bool colavacia(){return pi==(pf+1)%MAX;};
    bool colallena(){return pi==(pf+2)%MAX;};
    void encolar(int a);
    void desencolar();
    int ultimo();
    string imprimir(string s);
};

#endif //MAIN_CPP_COLA_TPP
