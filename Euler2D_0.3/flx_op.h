#ifndef FLX_OP_H_INCLUDED
#define FLX_OP_H_INCLUDED

#include <iostream>
#include "data.h"
#include "sit.h"

using namespace std;

data flx_op(sit& g, int i, vector<data>& w, int indOP, int indVnitrniBunky){
    data _flx;

    if(indOP == -1 || indOP == -2){ //stena

        _flx.rho    = 0.0;
        _flx.rhoU   = w[indVnitrniBunky].p() * g.stena[i].N.x;
        _flx.rhoV   = w[indVnitrniBunky].p() * g.stena[i].N.y;
        _flx.e      = 0.0;

        //cout << "---Printing boundary condition values - WALL:---" << endl
        //    << "p_f * sx = " << w[indVnitrniBunky].p() * g.stena[i].N.x
        //    << ",\t p_f * sy = " << w[indVnitrniBunky].p() * g.stena[i].N.y << endl;

    }else if(indOP == -4){  //vystup

        double pOut = 0.737;
        double rhoU = w[indVnitrniBunky].rhoU;
        double rhoV = w[indVnitrniBunky].rhoV;
        double rho = w[indVnitrniBunky].rho;
        vector <double> u = w[indVnitrniBunky].u();
        double eb = pOut / (kappa-1) + 0.5 * (rhoU*rhoU + rhoV*rhoV) / rho;

        double ubDOTn = g.stena[i].N.x * u[0] + g.stena[i].N.y * u[1];

        _flx.rho    = ubDOTn * rho;
        _flx.rhoU   = ubDOTn * rhoU + pOut*g.stena[i].N.x;
        _flx.rhoV   = ubDOTn * rhoV + pOut*g.stena[i].N.y;
        _flx.e      = ubDOTn * (eb + pOut);

        //cout << "---Printing boundary condition values - OUTLET:---" << endl
        //    << "ubx = " << u[0]
        //    << ",\t uby = " << u[1]
        //    << ",\t eb = "  << eb << endl;

    }else if(indOP == -3){  //vstup

        double p0 = 1.0;
        double T0 = 1.0;
        vector<double> dir(2);
        dir[0] = 1.0;
        dir[1] = 0.0;

        vector <double> u = w[indVnitrniBunky].u();
        double uLength = sqrt(u[0]*u[0]+u[1]*u[1]);
        double M1 = uLength / w[indVnitrniBunky].a();
        double pb = pow( (1+((kappa-1)/2)*M1*M1), (kappa/(1-kappa))) * p0;
        double Tb = T0 / (1+ ((kappa-1)/2)*M1*M1);
        vector<double> ub(2);
        double ab = sqrt(Tb);
        ub[0] = M1*ab*dir[0];
        ub[1] = M1*ab*dir[1];
        double uBLength = sqrt(ub[0]*ub[0]+ub[1]*ub[1]);
        double rhob = kappa*pb/Tb;
        double eb = pb / (kappa-1) + 0.5*rhob*uBLength*uBLength;

        double ubDOTn = g.stena[i].N.x * ub[0] + g.stena[i].N.y * ub[1];

        _flx.rho    = ubDOTn*rhob;
        _flx.rhoU   = ubDOTn*rhob*ub[0] + pb*g.stena[i].N.x;
        _flx.rhoV   = ubDOTn*rhob*ub[1] + pb*g.stena[i].N.y;
        _flx.e      = ubDOTn * (eb + pb);

        //cout << "---Printing boundary condition values - INLET:---" << endl
        //    << "M1 = " << M1 << ",\t pb = " << pb << ",\t Tb = "  << Tb << ",\t a = "  << w[indVnitrniBunky].a()
        //     << ",\t ab = "  << ab
        //    << ",\t ub length = "  << uBLength << ",\t rhob = "
        //    << rhob << ",\t eb = " << eb << endl;

        //cout << "---Printing boundary condition values - FLUX:---" << endl
        //    << "rho = " << _flx.rho
        //    << ",\t rhoU = " << _flx.rhoU
        //    << ",\t rhoV = " << _flx.rhoV
        //    << ",\t e = " << _flx.e
        //    << endl;

    }else{
        cout << "Neznamy index pomocne okrajove bunky!!!" << endl;
    }

    //cout << "---Printing boundary condition values - FLUX:---" << endl
    //        << "rho = " << _flx.rho
    //        << ",\t rhoU = " << _flx.rhoU
    //        << ",\t rhoV = " << _flx.rhoV
    //        << ",\t e = " << _flx.e
    //        << endl;

    return _flx;
}

#endif // FLX_OP_H_INCLUDED
