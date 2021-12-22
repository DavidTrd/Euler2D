#include "usecka.h"

usecka::usecka(){}

usecka::usecka(bod _P, bod _K){
    P.index = _P.index;
    P.x = _P.x;
    P.y = _P.y;

    K.index = _K.index;
    K.x = _K.x;
    K.y = _K.y;

    spocitejNormalu();
}

double usecka::delka(){
    return sqrt( pow(K.x-P.x, 2.0) + pow(K.y-P.y, 2.0) );
}

void usecka::spocitejNormalu(){
    double sx = K.x - P.x;
    double sy = K.y - P.y;

    //Slozky normaly
    N.x = sy;
    N.y = -sx;
}
