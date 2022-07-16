//
// Created by gino on 16/6/21.
//

#ifndef MAIN_CPP_BUSQUEDAAMPLITUD_H
#define MAIN_CPP_BUSQUEDAAMPLITUD_H
#include "BusquedaAmplitud.tpp"

void busqAmplitud::BEA(bool**&mAdy, int**& caminoHamil, int marca[], vector<coordenada> vCoord){

    int MAXNODOS = vCoord.size();
    int y;
    int x= 0;
    Cola Q;
    marca[x]=visitado;
    this->guardarReg(0,0);
    Q.encolar(x);
    while(!Q.colavacia()){
        x=Q.tope();
        Q.desencolar();
        for(y=0;y<MAXNODOS;y++){
            if((mAdy[x][y] == 1)&&(marca[y]==no_visitado)){
                marca[y]=visitado;
                Q.encolar(y);
                this->guardarReg(x,y);
            }
        }
    }
    caminoHamil = caminosH;
    /*cout<<"camino: "<<endl;
    for (int i = 0; i < maxV; i++){
        for (int j =0; j < maxV; j++)
            cout << " " << caminoHamil[i][j];

        cout<<endl;
    }*/

}
// caminosH={ {01 0 }  {3,4,5}}
// caminosH={ {0}{01 NULL} {02} {03} {...}{0,1,2,3,4}  {0,3,4,5}}
//
//
void busqAmplitud::guardarReg(int x,int y) {

    if (x == 0 && y == 0) {
        caminosH[0][0] = 0;
        return;
    }
    for (int i = 0; i < cantV; i++){
        for (int j = 0; j < cantV; j++) {
            if (caminosH[i][j] == x && caminosH[i][j + 1] == -1) {
                caminosH[i][j + 1] = y;
                return; // sino usar bandera
            } else if (caminosH[i][j] == x && caminosH[i][j + 1] != -1) {
                // entonces hago una copia del camino pero en j+1 le pongo el y
                // me voy a la fila mas proxima k con un -1 en [k,0]
                for (int k = i; k < cantV; k++)
                    if (caminosH[k][0] == -1) {
                        c = k;
                        break;
                    }
                for (int k = 0; k <= j; k++)
                    caminosH[c][k] = caminosH[i][k];

                caminosH[c][j + 1] = y;
                return;
            }
        }
    }
}


#endif //MAIN_CPP_BUSQUEDAAMPLITUD_H
