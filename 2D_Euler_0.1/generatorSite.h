#ifndef GENERATORSITE_H_INCLUDED
#define GENERATORSITE_H_INCLUDED
#include <vector>
#include <cmath>

using namespace std;

void generatorSite(vector<double>& x, vector<double>& y, int nX, int nY){
    x.resize(0);
    y.resize(0);

    //Vyska a delka vypocetni oblasti
    double H = 1.0, L = 3.0;

    //Velikost kroku site v obou smerech:
    double dX = L / double(nX);
    double dY = H / double(nY);

    //Koeficient prechodu z kruznice na ucecku
    double q = 1.0 / nY;

    //Index bodu (uzlu)
    int k = 0;

    for(int j = 0; j <= nY; j++){
        for(int i = 0; i <= nX; i++){

            //Body lezi na primce
            x.push_back(i*dX);
            y.push_back(j*dY);

            if(x[k] > 1.0 && x[k] < 2.0){
                //Body lezi na kruznici
                y[k] = j*dY + (1.0 - j*q)*(sqrt(1.3*1.3 - pow(x[k]-1.5, 2.0)) - 1.2);
            }
            ++k;
        }
    }

    //for(int l = 0; l < x.size(); l++){
    //    cout << x[l] << ", " << y[l] << endl;
    //}
}

#endif // GENERATORSITE_H_INCLUDED
