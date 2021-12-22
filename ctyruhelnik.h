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

#endif // CTYRUHELNIK_H_INCLUDED
