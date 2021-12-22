#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <cmath>
#include <vector>

#define kappa 1.4

using namespace std;

class data{
public:
    double rho, rhoU, rhoV, e;  //Slozky vektoru neznamych

    data F();   //Metody vracejici tok ve smeru x a y
    data G();

    double a(); //Metada pro vypocet rychl. zvuku
    double p(); //Metoda pro vypocet tlaku
    vector<double> u(); //Metoda pro vypocet vektoru rychlosti
};

data data::F(){
    data _pom;

    _pom.rho    = rhoU;
    _pom.rhoU   = rhoU * rhoU/rho + p();
    _pom.rhoV   = rhoU * rhoV/rho;
    _pom.e      = (e + p()) * rhoU/rho;

    return _pom;
}

data data::G(){
    data _pom;

    _pom.rho    = rhoV;
    _pom.rhoU   = rhoU * rhoV/rho;
    _pom.rhoV   = rhoV * rhoV/rho + p();
    _pom.e      = (e + p()) * rhoV/rho;

    return _pom;
}

double data::a(){
    return sqrt(kappa * p() / rho);
}

double data::p(){
    return (kappa - 1.0) * (e - 0.5*rho*(pow(rhoU/rho, 2.0) + pow(rhoV/rho, 2.0)));
}

vector<double> data::u(){
    vector<double> _u(2);

    _u[0] = rhoU / rho;
    _u[1] = rhoV / rho;

    return _u;
}

//Pretizeni operatoru:
inline data operator+ (const data& _A, const data& _B){
    data _C;

    _C.rho  = _A.rho    + _B.rho;
    _C.rhoU = _A.rhoU   + _B.rhoU;
    _C.rhoV = _A.rhoV   + _B.rhoV;
    _C.e    = _A.e      + _B.e;

    return _C;
}

inline data operator- (const data& _A, const data& _B){
    data _C;

    _C.rho  = _A.rho    - _B.rho;
    _C.rhoU = _A.rhoU   - _B.rhoU;
    _C.rhoV = _A.rhoV   - _B.rhoV;
    _C.e    = _A.e      - _B.e;

    return _C;
}

inline data operator* (const double& _k, const data& _A){
    data _C;

    _C.rho  = _k * _A.rho;
    _C.rhoU = _k * _A.rhoU;
    _C.rhoV = _k * _A.rhoV;
    _C.e    = _k * _A.e;

    return _C;
}

inline data operator/ (const data& _A, const double& _k){
    data _C;

    _C.rho  = _A.rho    / _k;
    _C.rhoU = _A.rhoU   / _k;
    _C.rhoV = _A.rhoV   / _k;
    _C.e    = _A.e      / _k;

    return _C;
}

#endif // DATA_H_INCLUDED
