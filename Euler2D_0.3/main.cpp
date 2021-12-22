#include <iostream>
#include <vector>

#include "data.h"
#include "flx.h"
#include "flx_op.h"
#include "sit.h"
#include "generatorSite.h"
#include "ctyruhelnik.h"
#include "naplnSit.h"
#include "vektor2D.h"
#include "ulozVysledkyGnp.h"
#include "ulozVysledkyVtk.h"
#include "casovyKrok.h"

using namespace std;

int main()
{
    //Vektory pro souradnice uzlovych bodu site
    vector<double> x, y;
    vector<data> w, wn, rez;
    sit g;

    //Pocet bunek ve smeru X a Y:
    //int nX = 9, nY = 3;
    int nX = 150, nY = 50;

    generatorSite(x, y, nX, nY);

    naplnSit(x, y, nX, nY, g);

    //---PRINT GRID INFO--------------------------------------
 /*   for(int i = 0; i < g.stena.size(); i++){

        double Lvol = 0, Rvol = 0;
        if(g.stena[i].indBunLev >= 0){
            Lvol = g.bunka[g.stena[i].indBunLev].plocha();
        }
        if(g.stena[i].indBunPra >= 0){
            Rvol = g.bunka[g.stena[i].indBunPra].plocha();
        }

        cout << "Stena = " << i
            << ";\t Bunka L = " << g.stena[i].indBunLev
            << ";\t L vol = " << Lvol
            << ";\t Bunka R = " << g.stena[i].indBunPra
            << ";\t R vol = " << Rvol
            << ";\t Nx = " << g.stena[i].N.x
            << ";\t Ny = " << g.stena[i].N.y
            << ";\t N delka = " << g.stena[i].N.delk()
            << ";\t P = " << g.stena[i].P.x
            << ";\t P = " << g.stena[i].P.y
            << ";\t K = " << g.stena[i].K.x
            << ";\t K = " << g.stena[i].K.y
            << endl;
    }
*/
    //---END OF PRINT GRID INFO-------------------------------

    w.resize(g.bunka.size());
    wn.resize(g.bunka.size());
    rez.resize(g.bunka.size());

    //Pocatecni podminky
    for(int i = 0; i < g.bunka.size(); i++){
        w[i].rho = 1.4;
        w[i].rhoU = 0.14;
        w[i].rhoV = 0.0;
        w[i].e = 1.0 / 0.4;
    }

    //TODO: Vypocet dt z podminky stability!!!
    double dt = 0.8*0.00446, t = 0.0, tEnd = 30;
    int iter = 0;

    //Vypocetni cyklus
    while(t <= tEnd){
        //Navyseni simulovaneho casu
        t += dt;

        //1) vypocet rezidua pres vsechny steny bunek
        for(int i = 0; i < g.stena.size(); i++){
            if(g.stena[i].indBunPra >= 0 && g.stena[i].indBunLev >= 0){
                rez[g.stena[i].indBunPra] = rez[g.stena[i].indBunPra]
                                            - flx(g, i, w);
                rez[g.stena[i].indBunLev] = rez[g.stena[i].indBunLev]
                                            + flx(g, i, w);
            }else if(g.stena[i].indBunPra < 0){
                rez[g.stena[i].indBunLev] = rez[g.stena[i].indBunLev]
                    + flx_op(g, i, w, g.stena[i].indBunPra, g.stena[i].indBunLev);
            }else if(g.stena[i].indBunLev < 0){
                rez[g.stena[i].indBunPra] = rez[g.stena[i].indBunPra]
                    - flx_op(g, i, w, g.stena[i].indBunLev, g.stena[i].indBunPra);
            }
        }

        //Vypocet hodnot v nove casove vrstve:
        for(int i = 0; i < g.bunka.size(); i++){
            //cout << "REZ = " << rez[i].rho << endl;
            wn[i] = w[i] - dt * rez[i] / g.bunka[i].plocha();
        }

        //Prekopirovani hodnot do nove casove vrstvy:
        for(int i = 0; i < g.bunka.size(); i++){
            w[i] = wn[i];
            rez[i].rho = 0.0;
            rez[i].rhoU = 0.0;
            rez[i].rhoV = 0.0;
            rez[i].e = 0.0;
        }

        iter++;

        if(iter%10 == 0){
            cout << "iter = " << iter << ", time = " << t << ", dt = " << dt << ", rho[10] = " << w[10].rho << endl;
        }
    }

    //Ulozeny vysledku
    ulozVysledkyGnp(g, w);
    ulozVysledkyVtk(g, w);

    return 0;
}
