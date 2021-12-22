#ifndef USECKA_H_INCLUDED
#define USECKA_H_INCLUDED

#include <cmath>
#include "bod.h"
#include "vektor2D.h"

class usecka{
public:
    usecka();
    usecka(bod _P, bod _K);
    ~usecka(){}
    int index;
    int indBunLev;
    int indBunPra;
    bod P;  //pocatecni bod usecky
    bod K;  //koncovy bod usecky
    vektor2D N; //normalovy vektor k usecce
    double delka();
    void spocitejNormalu();
};

#endif // USECKA_H_INCLUDED
