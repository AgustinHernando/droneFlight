//
// Created by gino on 14/6/21.
//
#ifndef VUELODRONE_V00_GRAFOS_H
#define VUELODRONE_V00_GRAFOS_H
#include "Grafos.tpp"
#include <cmath>

using namespace std;

bool operator-(segmento seg1, segmento seg2) {

    int x = seg2.c1.x;
    int y = seg2.c1.y;

    int ax = seg1.c1.x;
    int ay = seg1.c1.y;

    int bx = seg1.c2.x;
    int by = seg1.c2.y;

    //max retorna el int mas grande ;; min retorna el int mas chico
    if (x <= max(ax, bx) && x >= min(ax, bx) &&
        y <= max(ay,by) && y >= min(ay,by))
        return true;

    x = seg2.c2.x;
    y = seg2.c2.y;

    if (x <= max(ax, bx) && x >= min(ax, bx) &&
        y <= max(ay,by) && y >= min(ay,by))
        return true;
    return false;
}

/*
// encuentra la orientacion de los puntos en el siguiente orden (p, q, r).
// p es el punto de partida para ambos vectores
// 0 --> p, q r son colineales
// 1 --> sentido horario
// 2 --> sentido antihorario
 */
int operator>>(segmento seg1, coordenada punto) {
    //producto cruz para saber el sentido    (RQ)x(QP)
    int val = (seg1.c1.y - punto.y) * (seg1.c2.x - punto.x) -
              (seg1.c1.x - punto.x) * (seg1.c2.y - punto.y);
    //por definicion si el producto cruz da 0
    if (val == 0) return 0; // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

/*
    // analizo las orientaciones
    // hago producto cruz entre vectores que parten  de la primer coordenada
    // que recibe como parametro el metodo orientacion y se interpretan 2 vectores,
    // uno hasta el segundo parametro y otro hasta el tercer parametro
     */
bool operator|(segmento seg1, segmento seg2){

    int o1 = seg1 >> seg2.c1;
    int o2 = seg1 >> seg2.c2;
    int o3 = seg2 >> seg1.c1;
    int o4 = seg2 >> seg1.c2;

    // Casos:
    //general
    if (o1 != o2 && o3 != o4)
        return true;

    //especiales
    // colineares pero se contienen
    if (o1 == 0 && seg1-seg2) return true;
    if (o2 == 0 && seg1-seg2) return true;
    if (o3 == 0 && seg2-seg1) return true;
    if (o4 == 0 && seg2-seg1) return true;

    return false; // si no entran en colineares encimadas entonces no se intersectan
}

bool** Grafos::crearMatriz(int n){
    bool **maux;
    // reservo lugar en memoria para un "array" de punteros a punteros
    maux = (bool**)calloc(n, sizeof (bool*));

    // en cada posicion del "array", reservo memoria para sus columnas
    for (int i = 0; i < n; i++)
        maux[i] = (bool*)calloc(n, sizeof(bool));

    // inicializo la matriz con ceros
    for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++)
            maux[j][k] = 0;

    // devuelvo matriz nxn
    return maux;
}

void Grafos::setGrafo(string fila, bool**&m, bool**&o, bool**&v,bool**&vaux,int f, int n){ //recibe una fila completa por ejemplo  "00000111000x0001110000000000"
    for(int i = 0; i < n; i++) {
        if(fila[i] == '1'){
            m[f][i] = 1;            //setear la posicion donde hay maleza a 1
            vaux[f][i] = 1;         //y genero una copia de la matriz de malezas en la matriz de vertices auxiliar
        }else if( fila[i] == 'x'){
            o[f][i] = 1;
        }
    }
}

// busca los vertices dentro de la matriz de malezas
void Grafos::buscarVertices(bool**& vaux,bool**& v, vector<coordenada> &vcord, int size){
    // busco los vertices
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(vaux[i][j] == 1) {
                int t = tamanioMaleza(vaux, size, i, j);
                // caso 1: maleza de superficie > 9 ==> vertice = esquina superior izq
                if (t > 9) {
                    v[i][j] = 1;
                    vcord.push_back({i,j});
                }
                // caso 2: maleza de superficie 9 ==> vertice: centro de la matriz
                if (t == 9) {
                    v[i + 1][j + 1] = 1;
                    vcord.push_back({i+1,j+1});
                }
            }
        }
    }

}

int Grafos::tamanioMaleza(bool**v, int size, int i, int j){   // i,j=0,7
    int k, l = j, contador=0;
    for (k = i; k < size; k++) {
        if( v[k][l] == 0 )  break;
         for(l = j; l <= size; l++){
                if(v[k][l] == 1){
                    // a medida que vaya encontrando 1 en la copia de la matriz de malezas, los voy reemplazando por 0,
                    // para que cuando despues siga recorriendo la matriz no vuelva a leer un sector de la misma maleza
                    v[k][l] = 0;
                    contador++;     //indica cuando converti un valor de 1 a 0
                }
                else{
                    l = j;
                    break;
                }
           }
    }
    return contador;
}

void Grafos::printGrafo(bool** m, int f){
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < f; j++) {
            (m[i][j] == 1 ? cout << "1" : cout << "0");
        }
        cout << endl;
    }
}

/* la siguiente funcion busca las coordenas inicial y final de un obstaculo
 * utiliza la funcion auxiliar 'coordObs', la cual busca barreras horizontales o verticales, en ese orden
 */
void Grafos::buscarObstaculos(bool**o, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (o[i][j] == 1) {
                coordObs(o, size, i, j);
            }
        }
    }
}

void Grafos::coordObs(bool**&o, int size, int i, int j) {
    int contador = 0;
    coordenada c1={i,j};
    coordenada c2 = {0,0};

    if(o[i][j+1]==1)
    {
        for(int l=j+1;l<size;l++){
            if(o[i][l]==1){
                o[i][l]= 0;
                contador++;
            }
            else{
                break;
            }
        }
        c2 = {i,j+contador};
    }
    else{
        if(o[i+1][j]==1)
        {
            for(int k=i + 1;k<size;k++)
            {
                if(o[k][j]==1){
                    o[k][j]= 0;
                    contador++;
                }else{
                    break;
                }
            }
            c2 = {i+contador,j};
        }
    }
    rObstaculo.push_back({c1, c2});
}

void Grafos::printVObstaculos(){
    cout << "\nVECTOR DE OBSTACULOS\n";
    for(int i = 0; i < rObstaculo.size(); i++) {
        cout<<"A"<<i<<": ("<<rObstaculo[i].c1.x<<","<<rObstaculo[i].c1.y<<") al"<<" ("<<rObstaculo[i].c2.x<<","<<rObstaculo[i].c2.y<<")"<<endl;
    }
}

//devuelve las vAristas, tengo que ver si las Aristas que unen los vertices se interceptan con los obstaculos
void Grafos::setAristas( vector<coordenada> pVert){
    int c = 0;
    bool b;
    segmento arista;
    //cout<<pVert.size()<<endl;
    while( c < pVert.size() - 1 ){
        //cout<<c<<endl;
        for (int j = c + 1; j < pVert.size(); j++) {
            b = true;
            arista = {pVert[c], pVert[j]};// agarra una arista y va probando si la recta con cada una de las demas aristas se choca con un obstaculo
            //cout<<"A"<<": ("<<arista.c1.x<<","<<arista.c1.y<<") al"<<" ("<<arista.c2.x<<","<<arista.c2.y<<")"<<endl;
            for (int i = 0; i < rObstaculo.size(); i++) {
                //cout<<"O"<<i<<": ("<<rObstaculo[i].c1.x<<","<<rObstaculo[i].c1.y<<") al"<<" ("<<rObstaculo[i].c2.x<<","<<rObstaculo[i].c2.y<<")"<<endl;
                if (rObstaculo[i] | arista) {
                    b = false;
                    break;
                } // '|' es para preguntar si se intersectan;;; aca se fija
            }
            if (b) {
                rAristas.push_back(arista);
            }
        }
        c++;
    }
     cout<<endl<<"ARISTA: "<<endl;
     for (int i = 0; i < rAristas.size(); ++i) {
         cout<<"A"<<i<<": ("<<rAristas[i].c1.x<<","<<rAristas[i].c1.y<<") al"<<" ("<<rAristas[i].c2.x<<","<<rAristas[i].c2.y<<")"<<endl;
     }
}
bool operator==(coordenada c1, coordenada c2){
    if(c1.x == c2.x && c1.y == c2.y) return true;
    return false;
}

void Grafos::getMatrizAdy(vector<coordenada> pVert, bool**& MatrizAdy) {
    MatrizAdy = crearMatriz(pVert.size());
    setAristas(pVert);
    coordenada v;

    for (int i = 0; i < pVert.size(); i++){
        for(int j= 0; j< rAristas.size(); j++){
            v = pVert[i];
            if(rAristas[j].c1 ==  v){
                v= rAristas[j].c2;
            }else if( rAristas[j].c2 == v ){
                v= rAristas[j].c1;
            }
            if (!(v == pVert[i])){
                for (int k = 0; k < pVert.size(); k++) {
                    if(v==pVert[k]){
                        MatrizAdy[k][i] = 1;
                        MatrizAdy[i][k] = 1;
                        break;
                    }
                }
            }
        }
    }
}

#endif //VUELODRONE_V00_GRAFOS_H
