#ifndef FLX_OP_H_INCLUDED
#define FLX_OP_H_INCLUDED

#include <iostream>
#include "data.h"
#include "include/sit.h"

using namespace std;

data flx_op(sit& g, int i, vector<data>& w, int indOP, int indVnitrniBunky){
    data _flx;

    if(indOP == -1 || indOP == -2){ //stena

        _flx.rho    = 0.0;
        _flx.rhoU   = w[g.bunka[indVnitrniBunky]].p() * g.stena[i].N.x;
        _flx.rhoV   = w[g.bunka[indVnitrniBunky]].p() * g.stena[i].N.y;
        _flx.e      = 0.0;
    }else if(indOP == -3){  //vystup

        double pOut = 0.737;
        double rhoU = w[g.bunka[indVnitrniBunky]].rhoU;
        double rhoV = w[g.bunka[indVnitrniBunky]].rhoV;
        double rho = w[g.bunka[indVnitrniBunky]].rho;
        vector <double> u = w[g.bunka[indVnitrniBunky]].u();
        double eb = pOut / (kappa-1) + 0.5 * (rhoU*rhoU + rhoV*rhoV) / rho;

        double ubDOTn = g.stena[i].N.x * u[0] + g.stena[i].N.y * u[1];

        _flx.rho    = ubDOTn * rho;
        _flx.rhoU   = ubDOTn * rhoU + pOut*g.stena[i].N.x;
        _flx.rhoV   = ubDOTn * rhoV + pOut*g.stena[i].N.y;
        _flx.e      = ubDOTn * (eb + pOut);
    }else if(indOP == -4){  //vstup

        double p0 = 1.0;
        double T0 = 1.0;
        vector<double> dir(1.0, 0.0);

        vector <double> u = w[g.bunka[indVnitrniBunky]].u();
        double uLength = sqrt(u[0]*u[0]+u[1]*u[1]);
        double M1 = uLength / w[g.bunka[indVnitrniBunky]].a();
        double pb = pow( (1+(kappa-1)/(2*M1*M1)), (kappa/(1-kappa))) * p0;
        double Tb = T0 / (1+ (kappa-1)/(2*M1*M1));
        vector<double> ub(2);
        ub[0] = M1*sqrt(Tb)*dir[0];
        ub[1] = M1*sqrt(Tb)*dir[1];
        double rhob = kappa*pb/Tb;
        double eb = pb / (kappa-1) + 0.5*rhob*uLength*uLength;

        double ubDOTn = g.stena[i].N.x * u[0] + g.stena[i].N.y * u[1];

        _flx.rho    = ubDOTn*rhob;
        _flx.rhoU   = ubDOTn*rhob*ub[0] + pb*g.stena[i].N.x;
        _flx.rhoV   = ubDOTn*rhob*ub[1] + pb*g.stena[i].N.y;
        _flx.e      = ubDOTn * (eb + pb);
    }else{
        cout << "Neznamy index pomocne okrajove bunky!!!" << endl;
    }

    return _flx;
}

#endif // FLX_OP_H_INCLUDED
