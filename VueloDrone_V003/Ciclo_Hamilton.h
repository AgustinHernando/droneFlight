//
// Created by gino on 14/6/21.
//
#ifndef VUELODRONE_V00_CICLO_HAMILTON_H
#define VUELODRONE_V00_CICLO_HAMILTON_H
#include <iostream>
#include "Ciclo_Hamilton.tpp"

using namespace std;



Hamilton::Hamilton() {}

double operator&(coordenada c1, coordenada c2) {
    double distancia;
    int x,y;
    x= c2.x - c1.x;
    y= c2.y - c1.y;
    distancia= sqrt( pow(x,2) + pow(y,2) );
    return distancia;
}


// Verifica si el vertice 'v' puede ser agregado en la posicion 'pos' del ciclo hamilton construido
bool Hamilton::caminoViable(int v, bool **grafico, vector<int> camino, int pos){
    // verifica si un vertice es adyacente al vertice agregado previamente
    if (grafico[camino[pos - 1]][ v ] == 0)
        return false;

    // verifica si el vertice ya esta incluido.
    for (int i = 0; i < pos; i++)
        if (camino[i] == v)
            return false;

    return true;
}
// funcion recursiva para el ciclo Hamilton
bool Hamilton::hamiltonAux(bool **grafico, vector<int>& camino, int pos){
    // caso base: los vertices estan incluidos en el Ciclo Hamilton
    if (pos == nvert){
        // pregunta si hay un vertice desde el ultimo vertice agregado hasta el primer vertice
        if (grafico[camino[pos - 1]][camino[0]] == 1)
            return true;
        else
            return false;
    }

    // prueba diferentes vertices como proximo candidato pertenenciente al ciclo hamilton
    // empieza en 1 porque asumimos que el vertice 0 es el punto de partida
    for (int v = 1; v < nvert; v++){
        // pregunta si el vertice 'v' puede ser agregado al ciclo hamilton. De ser asi, lo agrega
        if (caminoViable(v, grafico, camino, pos)){
            camino[pos] = v;    // agregar camino de profundidad, por ejemplo [0, 5, 4] del jamboard

            // si hay camino, llama recursivamente para construir el resto del camino, aumentando la posicion en cada recursion
            if (hamiltonAux(grafico, camino, pos+1)) //pedirSiguiente()
                return true;
            // remueve el vertice 'v' si no hay un camino dirigido digamos, o bien, si no hay solucion
            camino[pos] = -1;
        }
    }
    // si ningun vertice puede ser agregado al ciclo hamilton hasta cierto punto, devuelve false
    return false;
}

/*  Esta funcion usa "backtracking" para resolver el ciclo hamilton
    Utiliza la funcion booleana 'cicloHamilton()' para resolver el problema
    Al haber mas de una solucion posible, esta funcion imprime una de las posibilidades
*/
bool Hamilton::cicloHamilton(bool **grafico, vector<coordenada> vCoor, vector<int> camino){
    /*  El vertice 0 es el punto de partida como primicia.
        En realidad, puede ser cualquiera porque el ciclo hamilton tiene que poder volver al punto de paertida dado.
    */

    this->nvert = vCoor.size();
    a = camino.size();
    for (int i = camino.size(); i < nvert; i++)
        camino.push_back(-1);

    //imprimirSolucion(camino);
    // pregunta si no hay solucion posible
    if (!hamiltonAux(grafico, camino, a)){ // tenia un '1'
        cout << "\nNo hay solucion";
        return false;
    }
    imprimirSolucion(camino);
    Distancia(camino, vCoor);
    return true;
}



void Hamilton::imprimirSolucion(vector<int> camino){
    cout << "\nEncontramos un posible Ciclo Hamiltoniano\n";
    for (int i = 0; i < nvert; i++)
        cout << camino[i] << " <--> ";

    // imprime el punto de partida para hacer enfasis al "ciclo"
    cout << camino[0] << " " << endl;
}
void Hamilton::Distancia(vector<int> camino, vector<coordenada> vCoor){
    double acum1,acum2= 0;
    acum1 = calcularDistancia(camino, vCoor);
    if(!b)acum2 = calcularDistancia(this->caminoAux, vCoor);
    if(b){
        caminoAux = camino;
        b=false;
    }else{
        if(acum1 < acum2){
            caminoAux = camino;
            acumm = acum1;
        }
    }
    cout << "\nLa distancia es: "<<acum1<<endl;
}
double Hamilton::calcularDistancia(vector<int> camino, vector<coordenada> vCoor) {
    double acum= 0 ;
    int p, r;

    for (int i = 1; i < vCoor.size(); i++) {
        p = camino[i - 1];
        r = camino[i];
        acum += vCoor[p] & vCoor[r];
    }
    acum += vCoor[vCoor.size() -1] & vCoor[0];
    return acum;
}

void Hamilton::MejorCamino(){
    cout << "\n-------------------------------()()()()()()-- >LA DISTANCIA MAS CORTA ES< --()()()()()()------------------------------- "<<endl<<acumm<<endl;
    cout << "\n()()()()()()******************>EL DRONE DEBERA PASAR POR LAS SIGUIENTES COORDENADAS<******************()()()()()()\n";
    for (int i = 0; i < nvert; i++)
        cout << caminoAux[i] << " --> ";
    cout << caminoAux[0] << " ";
    cout<<endl;
    for (int i = nvert; i > 0; i--)
        cout << caminoAux[i] << " <-- ";
    // imprime el punto de partida para hacer enfasis al "ciclo"
    cout << caminoAux[0] << " ";
}


#endif //VUELODRONE_V00_CICLO_HAMILTON_H
