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
        GestionVacunas* gestionVacunas = new GestionVacunas(argv[1],argv[2],argv[3]);

        vector<string> vecAuxilia = gestionVacunas->listadoNSS();
        vector<int> vecAuxiliaBool;
        for(int i = 0; i < vecAuxilia.size();++i){
            vecAuxiliaBool.push_back(0);
        }

        for (int i = 0; i < vecAuxilia.size(); ++i){
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
                    }*/
                }
            }
        }
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}