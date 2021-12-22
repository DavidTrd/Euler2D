#ifndef ULOZVYSLEDKYGNP_H_INCLUDED
#define ULOZVYSLEDKYGNP_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>

#include "sit.h"
#include "data.h"

using namespace std;

void ulozVysledkyGnp(sit& g, vector<data>& w){

    ofstream myfile;
    myfile.open ("vysledkyGnp.txt");

    myfile << "#File for Gnuplot." << endl;
    myfile << "#Pocet bunek v siti: " << g.bunka.size() << endl;
    myfile << "#Variables: x y rho u v e p Ma" << endl;

    ///TODO: Pouzivat souradnice teziste bunek

    for(int i = 0; i < g.bunka.size(); i++){
        myfile << g.bunka[i].vrchol[0].x << "\t" << g.bunka[i].vrchol[0].y
        << "\t" << w[i].rho
        << "\t" << w[i].rhoU/w[i].rho
        << "\t" << w[i].rhoV/w[i].rho
        << "\t" << w[i].e
        << "\t" << w[i].p()
        << "\t" << sqrt( pow(w[i].rhoU/w[i].rho, 2.0) + pow(w[i].rhoV/w[i].rho, 2.0) ) / w[i].a()
        << endl;
    }

    myfile.close();
}

#endif // ULOZVYSLEDKY_H_INCLUDED
