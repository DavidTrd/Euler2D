#ifndef CTYRUHELNIK_H_INCLUDED
#define CTYRUHELNIK_H_INCLUDED

#include <vector>
#include "usecka.h"

using namespace std;

class ctyruhelnik{
public:
    ctyruhelnik();
    ctyruhelnik(usecka _a, usecka _b, usecka _c, usecka _d);
    int index;
    double plocha();

    vector<bod> vrchol;
    vector<usecka> hrana;
};

ctyruhelnik::ctyruhelnik(){}

ctyruhelnik::ctyruhelnik(usecka _a, usecka _b, usecka _c, usecka _d){
    hrana.resize(0);
    vrchol.resize(0);

    hrana.push_back(_a);
    hrana.push_back(_b);
    hrana.push_back(_c);
    hrana.push_back(_d);

    vrchol.push_back(_a.P);
    vrchol.push_back(_b.P);
    vrchol.push_back(_c.P);
    vrchol.push_back(_d.P);
}

double ctyruhelnik::plocha(){
    double a = hrana[0].delka();
    double b = hrana[1].delka();
    double c = hrana[2].delka();
    double d = hrana[3].delka();

    usecka diagonala(vrchol[0], vrchol[2]);
    double e = diagonala.delka();

    //plocha trojuhelniku abe (A1)
    double s1 = 0.5 * (a + b + e);
    double A1 = sqrt( s1*(s1-a)*(s1-b)*(s1-e));

    //plocha trojuhelniku cde (A2)
    double s2 = 0.5 * (c + d + e);
    double A2 = sqrt( s2*(s2-c)*(s2-d)*(s2-e));

    return A1 + A2;
}

#endif // CTYRUHELNIK_H_INCLUDED
