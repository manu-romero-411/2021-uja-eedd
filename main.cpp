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

        cout << "\n==== CONTADORES DE DOSIS DISPONIBLES (AL INSTANCIAR ESTÁN TODAS) ====" << endl;
        vector<int> contadores = gestionVacunas.getContadoresVacunasTipo();
        string fabricantes[4] = {"Pfizer","Moderna","AstraZeneca","Johnson"};
        for (int i = 0; i < contadores.size(); ++i){
            cout << fabricantes[nombreFabricante(i)] << " -> " << contadores[i] << endl;
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

        cout << "\n==== ADMINISTRAR DOSIS A MAYORES DE 65 ====" << endl;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            Usuario* vacunable = gestionVacunas.buscarUsuario(vecAuxilia[i]);
            if(vacunable) {
                if (vacunable->getedad() >= 65) {
                    CentroVacunacion *centro = gestionVacunas.centroMasCercano(vacunable);
                    centro->anadirUsuarioLista(vacunable);
                    nombreFabricante fab = vacunable->getdosisRecomendable();
                    if(fab != ninguno){
                        if (centro->administrarDosis(vacunable, fab) ){
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

        cout << "\n==== ADMINISTRAR DOSIS A EVAS ====" << endl;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            Usuario* vacunable = gestionVacunas.buscarUsuario(vecAuxilia[i]);
            if(vacunable) {
                if (vacunable->getNombre() == "Eva") {
                    CentroVacunacion *centro = gestionVacunas.centroMasCercano(vacunable);
                    centro->anadirUsuarioLista(vacunable);
                    cout << "Nombre: " << vacunable->getNombre() << " " << vacunable->getApellidos() << " | ID: " << vacunable->getNss() <<
                         " | Dirección del centro: " << centro->getUbicacion().getLatitud() << ", " << centro->getUbicacion().getLongitud() << endl;
                    nombreFabricante fab = vacunable->getdosisRecomendable();
                    if(fab != ninguno){
                        if (centro->administrarDosis(vacunable, fab) ){
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
        cout << "\n==== CONTADORES DE DOSIS DISPONIBLES TRAS LAS VACUNACIONES ====" << endl;
        vector<int> contadores2 = gestionVacunas.getContadoresVacunasTipo();
        for (int i = 0; i < contadores2.size(); ++i){
            cout << fabricantes[nombreFabricante(i)] << " -> " << contadores2[i] << endl;
        }

        cout << "\n==== ADMINISTRAR DOSIS RESTANTES ====" << endl;
        cout << "Usuarios con sus listaDosis recomendadas: " << endl;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            Usuario* vacunable = gestionVacunas.buscarUsuario(vecAuxilia[i]);
            if(vacunable) {
                for (int j = 0; j < vacunable->dosisPorAdministrar(); ++j) {
                    CentroVacunacion *centro = gestionVacunas.centroMasCercano(vacunable);
                    centro->anadirUsuarioLista(vacunable);
                    nombreFabricante fab = vacunable->getdosisRecomendable();
                    if(fab != ninguno){
                        if (centro->administrarDosis(vacunable, fab) ){
                            vecAuxiliaBool[i] = 1;
                        } else {
                            vecAuxiliaBool[i] = -1;
                        }
                    } else {
                        vecAuxiliaBool[i] = -1;
                    }
                    if (vacunable->isDosisRec()){
                        cout << *vacunable << endl;
                    }
                }
            }
        }

        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}