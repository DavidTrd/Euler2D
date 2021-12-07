#ifndef FLX_H_INCLUDED
#define FLX_H_INCLUDED

#include <vector>
#include <iostream>

#include "data.h"
#include "include/sit.h"

using namespace std;

data flx(sit& g, int i, vector<double>& w){
    data _flx;

    //Upwind:
    vector<double> U(2);
    U = w[i].u();

    double uDotN = U[0]*g.stena[i].N.x + U[1]*g.stena[i].N.y;

    if(uDotN >= 0){
        _flx = uDotN * w[g.stena[i].indBunPra];
    }else{
        _flx = uDotN * w[g.stena[i].indBunLev];
    }

    return _flx;

}

#endif // FLX_H_INCLUDED
