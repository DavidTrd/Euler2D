#ifndef FLX_H_INCLUDED
#define FLX_H_INCLUDED

#include <vector>
#include <iostream>

#include "data.h"
#include "sit.h"

using namespace std;

data flx(sit& g, int i, vector<data>& w){
    data _flx;

    int cellL = g.stena[i].indBunLev;
    int cellR = g.stena[i].indBunPra;

    //Rusanov:
    vector<double> ul(2), ur(2);
    ul = w[cellL].u();
    ur = w[cellR].u();

    double pl = w[cellL].p();
    double pr = w[cellR].p();

    double ql = ul[0]*g.stena[i].N.x + ul[1]*g.stena[i].N.y;
    double qr = ur[0]*g.stena[i].N.x + ur[1]*g.stena[i].N.y;

    data Psil, Psir, pom;

    Psil.rho = w[cellL].rho;
    Psil.rhoU = w[cellL].rhoU;
    Psil.rhoV = w[cellL].rhoV;
    Psil.e = w[cellL].e + pl;

    Psir.rho = w[cellR].rho;
    Psir.rhoU = w[cellR].rhoU;
    Psir.rhoV = w[cellR].rhoV;
    Psir.e = w[cellR].e + pr;

    double al = w[cellL].a();
    double ar = w[cellR].a();
    double L = g.stena[i].N.delk();

    double c = 0.5*(fabs(ql)+al*L + fabs(qr)+ar*L);

    pom.rho = 0.0;
    pom.rhoU = g.stena[i].N.x;
    pom.rhoV = g.stena[i].N.y;
    pom.e = 0.0;

    _flx = 0.5*( ql*Psil + qr*Psir + (pl+pr)*pom
                - c*(w[cellR] - w[cellL]) );

    return _flx;

}

#endif // FLX_H_INCLUDED
