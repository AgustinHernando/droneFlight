#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include "Grafos.h"
#include "BusquedaAmplitud.h"
#include "Ciclo_Hamilton.h"

#define MAX 12
using namespace std;



int main() {
    Grafos *grafo = new Grafos();
    Hamilton *ham = new Hamilton();


    // definiendo matrices, que van a ser nxn
    bool **malezas;
    bool **obstaculos;
    bool **vertices;
    bool **verticesaux;
    bool **matrizAdy;
    int **caminosH;

    vector<coordenada> vCoord;
    vector<int> caminosVec;
    // de la coordenada (0,0) parte el dron
    vCoord.push_back({0,0});

    //obtencion de la matriz mediante un archivo de texto externo
    //cada bit separado por un espacio
    string fileName = "D:\\YOUR_PATH\\test\\txtMap.txt";
    fstream file;
    file.open(fileName.c_str());
    string word = "";

    int row = 0;
    int sizeOfRow = 0;

    // leyendo el archivo linea por linea...
    while(file >> word){
        if (row == 0){
            // cuando lee la primera row del archivo, obtengo el sizeOfRow y puedo inicializar las matrices
            sizeOfRow = word.size();
            malezas     = grafo->crearMatriz(sizeOfRow);
            obstaculos  = grafo->crearMatriz(sizeOfRow);
            vertices    = grafo->crearMatriz(sizeOfRow);
            verticesaux = grafo->crearMatriz(sizeOfRow);
        }
        // una vez inicializadas las matrices, las relleno con los valores correspondientes
        grafo->setGrafo(word, malezas, obstaculos, vertices, verticesaux, row, sizeOfRow);
        row++;
    }

    cout << "\nMAPA DE MALEZAS\n";
    grafo->printGrafo(malezas, sizeOfRow);

    cout << "\nMAPA DE OBSTACULOS\n";
    grafo->printGrafo(obstaculos, sizeOfRow);

    grafo->buscarVertices(verticesaux, vertices, vCoord, sizeOfRow);
    int cantV = vCoord.size();

    cout << "\nMAPA DE VERTICES\n";
    grafo->printGrafo(vertices, sizeOfRow);

    cout << "\nVECTOR DE COORDENADAS\n";
    for(int i = 0; i < cantV; i++) {
        cout<<"V"<<i<<": ("<<vCoord[i].x<<","<<vCoord[i].y<<")"<<endl;
    }

    grafo->buscarObstaculos(obstaculos, sizeOfRow);
    grafo->printVObstaculos();

    grafo->getMatrizAdy(vCoord, matrizAdy);
    cout<<"\nMATRIZ ADYACENCIA\n";
    grafo->printGrafo(matrizAdy,cantV);

    int marca[cantV];

    for(int i = 0; i < cantV; i++)
        marca[i] = 0;

    busqAmplitud *bAmp = new busqAmplitud(cantV);
    caminosH = (int**)calloc(cantV, sizeof (int*));
    // en cada posicion del "array", reservo memoria para sus columnas
    for (int i = 0; i < cantV; i++) {
        caminosH[i] = (int *) calloc(cantV, sizeof(int));
    }
    for (int i = 0; i < cantV; i++) {
        for (int j = 0; j < cantV; j++) {
            caminosH[i][j] = -1;
        }
    }

    // busca en anchura
    bAmp->BEA(matrizAdy, caminosH, marca, vCoord);


    // imprime la matriz que tiene las filas con los posibles caminos
    cout<<"camino listo: "<<endl;
    for (int i = 0; i < cantV; i++){
        for (int j =0; j < cantV; j++)
            cout << " " << caminosH[i][j];

        cout<<endl;
    }


    // leemos las filas de la matriz 'caminosH' y las mandamos al ciclo Hamilton
    for(int i = 0 ;i < cantV; i++){
        if(caminosH[i][0] == -1) break;
        for (int j = 0; j < cantV; ++j) {
            if(caminosH[i][j] != -1){
                caminosVec.push_back(caminosH[i][j]);
            }else if (caminosH[i][j] == -1){
                ham->cicloHamilton(matrizAdy, vCoord, caminosVec);
                caminosVec.clear();
                break;
            }
        }
        caminosVec.clear();
    }
    ham->MejorCamino();

    return 0;
}

