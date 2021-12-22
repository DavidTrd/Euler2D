#ifndef NAPLNSIT_H_INCLUDED
#define NAPLNSIT_H_INCLUDED

#include <vector>
#include "bod.h"
#include "usecka.cpp"
#include "ctyruhelnik.cpp"
#include "sit.h"

void naplnSit(vector<double> &x, vector<double> &y,
              int nX, int nY, sit &g){

    g.stena.resize(0);

    ///TODO: Osetrit orientaci sten pri prirazovani bunek!!!

    //Vsechny steny v radcich
    for(int i = 0; i <= nY; i++){
        for(int j = 0; j < nX; j++){
            bod P, K;
            int p = i*(nX+1) + j;
            int k = p + 1;
            P.x = x[p]; P.y = y[p];
            K.x = x[k]; K.y = y[k];

            ///TODO: nejdrive deklarovat usecku a pote do ni vlozit body
            if(i%2 == 0){
                if(j%2==0){
                    usecka pomStena(P, K);
                    g.stena.push_back(pomStena);
                }else{
                    usecka pomStena(K, P);
                    g.stena.push_back(pomStena);
                }
            }else{
                if(j%2==0){
                    usecka pomStena(K, P);
                    g.stena.push_back(pomStena);
                }else{
                    usecka pomStena(P, K);
                    g.stena.push_back(pomStena);
                }
            }

            int pomIndex = g.stena.size() - 1;

            //Indexy sousednich bunek
            if(i == 0){ //dolni stena - oznaceni ghost cell:
                if(j%2==0){
                    g.stena[pomIndex].indBunPra = -1;
                    g.stena[pomIndex].indBunLev = j;
                }else{
                    g.stena[pomIndex].indBunLev = -1;
                    g.stena[pomIndex].indBunPra = j;
                }
            }else if(i == nY){ //horni stena - oznaceni ghost cell:
                if(i%2==0){ //TODO: stridani!!!
                    if(j%2==0){
                        g.stena[pomIndex].indBunLev = -2;
                        g.stena[pomIndex].indBunPra = (i-1)*nX + j;
                    }else{
                        g.stena[pomIndex].indBunLev = (i-1)*nX + j;
                        g.stena[pomIndex].indBunPra = -2;
                    }
                }else{
                    if(j%2==0){
                        g.stena[pomIndex].indBunPra = -2;
                        g.stena[pomIndex].indBunLev = (i-1)*nX + j;
                    }else{
                        g.stena[pomIndex].indBunPra = (i-1)*nX + j;
                        g.stena[pomIndex].indBunLev = -2;
                    }
                }
            }else{ //vnitrni steny
                if(i%2!=0){
                    if(j%2==0){
                        g.stena[pomIndex].indBunPra = pomIndex;
                        g.stena[pomIndex].indBunLev = pomIndex - nX;
                    }else{
                        g.stena[pomIndex].indBunLev = pomIndex;
                        g.stena[pomIndex].indBunPra = pomIndex - nX;
                    }
                }else{
                   if(j%2==0){
                        g.stena[pomIndex].indBunLev = pomIndex;
                        g.stena[pomIndex].indBunPra = pomIndex - nX;
                    }else{
                        g.stena[pomIndex].indBunPra = pomIndex;
                        g.stena[pomIndex].indBunLev = pomIndex - nX;
                    }
                }
            }


        }
    }

    //Vsechny steny ve sloupcich
    for(int j = 0; j <= nX; j++){
        for(int i = 0; i < nY; i++){

            bod P, K;
            int p = j + i*(nX+1);
            int k = p + nX + 1;
            P.x = x[p]; P.y = y[p];
            K.x = x[k]; K.y = y[k];

            if(i%2 == 0){
                if(j%2==0){
                    usecka pomStena(K, P);
                    g.stena.push_back(pomStena);
                }else{
                    usecka pomStena(P, K);
                    g.stena.push_back(pomStena);
                }
            }else{
                if(j%2==0){
                    usecka pomStena(P, K);
                    g.stena.push_back(pomStena);
                }else{
                    usecka pomStena(K, P);
                    g.stena.push_back(pomStena);
                }
            }

            int pomIndex = g.stena.size() - 1;

            if(j == 0){
                //Leva OP (vstup -3)

                if(i%2==0){
                    g.stena[pomIndex].indBunPra = -3;
                    g.stena[pomIndex].indBunLev = i*nX;
                }else{
                    g.stena[pomIndex].indBunPra = i*nX;
                    g.stena[pomIndex].indBunLev = -3;
                }

            }else if(j == nX){
                //Prava OP (vystup -4)

                if(j%2 == 0){
                    if(i%2==0){
                        g.stena[pomIndex].indBunPra = (i+1)*nX-1;
                        g.stena[pomIndex].indBunLev = -4;
                    }else{
                        g.stena[pomIndex].indBunPra = -4;
                        g.stena[pomIndex].indBunLev = (i+1)*nX-1;
                    }
                }else{
                    if(i%2==0){
                        g.stena[pomIndex].indBunPra = -4;
                        g.stena[pomIndex].indBunLev = (i+1)*nX-1;
                    }else{
                        g.stena[pomIndex].indBunPra = (i+1)*nX-1;
                        g.stena[pomIndex].indBunLev = -4;
                    }
                }

            }else{
                //Vnitrni steny

                int vetsi = j + i*nX;
                int mensi = vetsi-1;

                if(j%2 == 0){
                    if(i%2==0){
                        g.stena[pomIndex].indBunPra = mensi;
                        g.stena[pomIndex].indBunLev = vetsi;
                    }else{
                        g.stena[pomIndex].indBunPra = vetsi;
                        g.stena[pomIndex].indBunLev = mensi;
                    }
                }else{
                    if(i%2==0){
                        g.stena[pomIndex].indBunPra = vetsi;
                        g.stena[pomIndex].indBunLev = mensi;
                    }else{
                        g.stena[pomIndex].indBunPra = mensi;
                        g.stena[pomIndex].indBunLev = vetsi;
                    }
                }

            }


        }
    }

    //Vsechny steny v radcich
    for(int i = 0; i < nY; i++){
        for(int j = 0; j < nX; j++){
            int indL, indP, indH, indD; //pomocne indexy sten bunky
            indD = j + i*nX;
            indH = j + (i+1)*nX;
            indL = (nX)*(nY+1) + i + j*nY;
            indP = (nX)*(nY+1) + i + (j+1)*nY;
            ctyruhelnik pomCtyr(g.stena[indD], g.stena[indP],
                                g.stena[indH], g.stena[indL]);
            g.bunka.push_back(pomCtyr);
        }
    }

}

#endif // NAPLNSIT_H_INCLUDED
