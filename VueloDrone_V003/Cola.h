//
// Created by gino on 16/6/21.
//

#ifndef MAIN_CPP_COLA_H
#define MAIN_CPP_COLA_H
#include "Cola.tpp"

//-------- Metodos de Cola --------------------
void Cola::encolar(int a)
{
    if (!colallena()){
        pf=(pf+1)%MAX;
        Q[pf]=a;
    }
    else cout<<"Cola llena"<<endl;
}

void Cola::desencolar(void)
{  if (!colavacia())pi=(pi+1)%MAX;
    else cout<<"Cola vacia"<<endl;
}
int Cola::ultimo(void)
{   return Q[pf];
}
string Cola::imprimir(string s)
{    if(!colavacia()){

        for(int i=pi;i!=pf+1;i=(i+1)%MAX)cout<<Q[i]<<"--";

    }

    return " <<< Q";
}
//------------------------------------------------------

#endif //MAIN_CPP_COLA_H
