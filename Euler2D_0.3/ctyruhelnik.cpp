#include "ctyruhelnik.h"

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
    usecka AB(vrchol[0], vrchol[1]);
    usecka BC(vrchol[1], vrchol[2]);
    usecka CD(vrchol[2], vrchol[3]);
    usecka DA(vrchol[3], vrchol[0]);
    //diagonala
    usecka AC(vrchol[0], vrchol[2]);

    double a = AB.delka();
    double b = BC.delka();
    double c = CD.delka();
    double d = DA.delka();
    double e = AC.delka();

    //plocha trojuhelniku abe (A1)
    double s1 = 0.5 * (a + b + e);
    double A1 = sqrt( s1*(s1-a)*(s1-b)*(s1-e));

    //plocha trojuhelniku cde (A2)
    double s2 = 0.5 * (c + d + e);
    double A2 = sqrt( s2*(s2-c)*(s2-d)*(s2-e));

    return A1 + A2;
}
