#ifndef ULOZVYSLEDKYVTK_H_INCLUDED
#define ULOZVYSLEDKYVTK_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>

#include "sit.h"
#include "data.h"

using namespace std;

void ulozVysledkyVtk(sit& g, vector<data>& w){

    ofstream myfile;
    myfile.open ("vysledkyVtk.txt");

    ///TODO: Zde vytiskout obsah souboru ve formatu VTK
    myfile << "...neco vytiskneme do souboru." << endl;





    myfile.close();
}
#endif // ULOZVYSLEDKYVTK_H_INCLUDED
