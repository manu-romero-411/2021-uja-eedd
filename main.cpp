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

        cout << "\n==== ADMINISTRAR A MAYORES DE 12 CUYO NSS NO ACABE EN 5 O 7 ====" << endl;
        vector<TarjetaVacunacion*> vecAuxilia;
        map<string,TarjetaVacunacion*> mapAuxilia = gestionVacunas.getListaTarjetas();
        for(std::map<string,TarjetaVacunacion*>::iterator it = mapAuxilia.begin();it!= mapAuxilia.end(); ++it){
            vecAuxilia.push_back(it->second);
        }
        cout << "Tamaño del vector auxiliar con los NSS: " << vecAuxilia.size() << endl;

        vector<int> vecAuxiliaBool;
        for(int i = 0; i < vecAuxilia.size();++i){
            vecAuxiliaBool.push_back(0);
        }

        for (int i = 0; i < vecAuxilia.size(); ++i){
            if(vecAuxilia[i]->getPropietario().getEdad() > 12 && stoi(vecAuxilia[i]->getPropietario().getNss())-5 %10 !=0 && stoi(vecAuxilia[i]->getPropietario().getNss())-7 %10 !=0 ){
                TarjetaVacunacion* tarjVacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(tarjVacunable){
                    CentroVacunacion* centro = gestionVacunas.centroMasCercano(&tarjVacunable->getPropietario());
                    centro->anadirTarjetaLista(tarjVacunable);
                    nombreFabricante fab = tarjVacunable->getFabricanteRecomendado();
                    if(fab != ninguno){
                        if (centro->administrarDosis(tarjVacunable, fab)){
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

        cout << "\n==== ADMINISTRAR DOSIS A MAYORES DE 25" << endl;

        for (int i = 0; i < vecAuxilia.size(); ++i){
            if(vecAuxilia[i]->getPropietario().getEdad() > 25 ){
                TarjetaVacunacion* vacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(vacunable){
                    CentroVacunacion* centro = gestionVacunas.centroMasCercano(&vacunable->getPropietario());
                    centro->anadirTarjetaLista(vacunable);
                    nombreFabricante fab = vacunable->getFabricanteRecomendado();
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

        cout << "El porcentaje de usuarios con pauta completa es: " << gestionVacunas.pautaCompleta(0) <<"%" <<endl;
        cout << "El porcentaje de usuarios con pauta completa en las nuevas condiciones es: " << gestionVacunas.pautaCompleta(1) <<"%" << endl;

        for (int i = 0; i < vecAuxilia.size(); ++i){
            if(vecAuxilia[i]->getPropietario().getEdad() >= 5 && vecAuxilia[i]->getPropietario().getEdad() <= 11){
                TarjetaVacunacion* tarjVacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(tarjVacunable){
                    CentroVacunacion* centro = gestionVacunas.centroMasCercano(&tarjVacunable->getPropietario());
                    centro->anadirTarjetaLista(tarjVacunable);
                    nombreFabricante fab = tarjVacunable->getFabricanteRecomendado();
                    if(fab != ninguno){
                        if (centro->administrarDosis(tarjVacunable, fab)){
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