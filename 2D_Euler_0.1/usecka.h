#ifndef USECKA_H_INCLUDED
#define USECKA_H_INCLUDED

#include <cmath>
#include "bod.h"
#include "vektor2D.h"

class usecka{
public:
    usecka();
    usecka(bod _P, bod _K);
    int index;
    int indBunLev;
    int indBunPra;
    bod P;  //pocatecni bod usecky
    bod K;  //koncovy bod usecky
    vektor2D N; //normalovy vektor k usecce
    double delka();
    void spocitejNormalu();
};

usecka::usecka(){}

usecka::usecka(bod _P, bod _K){
    P = _P;
    K = _K;
}

double usecka::delka(){
    return sqrt( pow(K.x-P.x, 2.0) + pow(K.y-P.y, 2.0) );
}

void usecka::spocitejNormalu(){
    double sx = K.x - P.x;
    double sy = K.y - P.y;

    N.delka = delka();

    //Jednotkova normala
    N.x = sy / N.delka;
    N.y = -sx / N.delka;
}

#endif // USECKA_H_INCLUDED
