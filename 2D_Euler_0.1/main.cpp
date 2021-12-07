#include <iostream>
#include <vector>

#include "data.h"
#include "flx.h"
#include "sit.h"
#include "generatorSite.h"
#include "ctyruhelnik.h"
#include "naplnSit.h"

using namespace std;

int main()
{
    //Vektory pro souradnice uzlovych bodu site
    vector<double> x, y;
    vector<data> w, wn, rez;
    sit g;

    //Pocet bunek ve smeru X a Y:
    int nX = 12, nY = 4;

    generatorSite(x, y, nX, nY);

    naplnSit(x, y, nX, nY, g);

    w.resize(g.bunka.size());
    wn.resize(g.bunka.size());
    rez.resize(g.bunka.size());

    //Pocatecni podminky
    for(int i = 0; i < g.bunka.size(); i++){
        w[i].rho = 1.0;
        w[i].rhoU = 1.0;
        w[i].rhoV = 1.0;
        w[i].e = 1.0;
    }

    //TODO: Vypocet dt z podminky stability!!!
    double dt = 1e-5, t = 0.0, tEnd = 1.0;

    //Vypocetni cyklus
    while(t <= tEnd){
        //Navyseni simulovaneho casu
        t += dt;

        //1) vypocet rezidua pres vsechny steny bunek
        for(int i = 0; i < g.stena.size(); i++){
            if(g.stena[i].indBunPra > 0){
                rez[g.stena[i].indBunPra] += flx(g, i, w);
            }else if(g.stena[i].indBunLev > 0){
                rez[g.stena[i].indBunLev] -= flx(g, i, w);
            }else if(g.stena[i].indBunPra < 0){
                rez[g.stena[i].indBunLev] -= flx_op(g, i, w, g.stena[i].indBunPra,
                                                    g.stena[i].indBunLev);
            }else if(g.stena[i].indBunlev < 0){
                rez[g.stena[i].indBunPra] += flx_op(g, i, w, g.stena[i].indBunLev,
                                                    g.stena[i].indBunPra);
            }
        }

        //Vydeleni rezidua plochou bunky
        for(int i = 0; i < g.bunka.size(); i++){
            rez[i] /= g.bunka[i].plocha();
        }

        //Vypocet hodnot v nove casove vrstve:
        for(int i = 0; i < g.bunka.size(); i++){
            wn[i] = w[i] - dt * rez[i];
        }
    }

    //Ulozeny vysledku
    //ulozVysledky();

    return 0;
}
