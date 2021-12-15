/*
 * File:   main.cpp
 * Author: Manuel Jesus Romero Mateos, Jose Ángel Ángeles Santiago
 *
 * Created on 22 de septiembre de 2021, 20:36
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Dosis.h"
#include "Usuario.h"
#include "GestionVacunas.h"
#include <chrono>
#include "THashTarjetaVacunacion.h"
#include "MallaRegular.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        cout << "==== INSTANCIACIÓN DE ARCHIVOS DENTRO DE GestionVacunas ====" << endl;
        GestionVacunas gestionVacunas(argv[1],argv[2],argv[3]);

        cout << "\n==== AÑADIR DOSIS A CENTROS DE VACUNACIÓN ====" << endl;
        vector<Dosis*> v;
        v = gestionVacunas.getDosis();
        int cuantas[5]={8000,8200,8500,5000,50};
        for (int i = 0; i < 5; ++i) {
            gestionVacunas.suministrarNdosisCentro(gestionVacunas.getCentros()[i], cuantas[i]);
        }
        cout << "\n==== ADMINISTRAR DOSIS A PARES ====" << endl;
        vector<string> vecAuxilia = gestionVacunas.listadoNSS();
        vector<int> vecAuxiliaBool;
        for(int i = 0; i < vecAuxilia.size();++i){
            vecAuxiliaBool.push_back(0);
        }

        for (int i = 0; i < vecAuxilia.size(); ++i){
            if((stoi(vecAuxilia[i]) % 2) == 0){
                Usuario* vacunable = gestionVacunas.buscarUsuario(vecAuxilia[i]);
                if(vacunable){
                    CentroVacunacion* centro = gestionVacunas.centroMasCercano(vacunable);
                    centro->anadirUsuarioLista(vacunable);
                    nombreFabricante fab = vacunable->getdosisRecomendable();
                    if(fab != ninguno){
                        if (centro->administrarDosis(vacunable, fab)){
                            vecAuxiliaBool[i] = 1;
                        } else {
                            vecAuxiliaBool[i] = -1;
                        }
                    } else {
                        vecAuxiliaBool[i] = -1;
                    }
                }
            }
        }




        /* for (int i = 0; i < vecAuxilia.size(); ++i){
             if((stoi(vecAuxilia[i]) % 2) == 0){
                 Usuario* vacunable = gestionVacunas->buscarUsuario(vecAuxilia[i]);
                 if(vacunable){
                     CentroVacunacion* centro = gestionVacunas->centroMasCercano(vacunable);
                     /*centro->anadirTarjetaLista(vacunable);
                     nombreFabricante fab = vacunable->getdosisRecomendable();
                     if(fab != ninguno){
                         if (centro->administrarDosis(vacunable, fab)){
                             vecAuxiliaBool[i] = 1;
                         } else {
                             vecAuxiliaBool[i] = -1;
                         }
                     } else {
                         vecAuxiliaBool[i] = -1;
                     }
                 }
             }
         }


         */
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}