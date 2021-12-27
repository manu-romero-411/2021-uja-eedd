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

        vector<TarjetaVacunacion*> doceCincoSiete;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            if(vecAuxilia[i]->getPropietario().getEdad() > 12 && stoi(vecAuxilia[i]->getPropietario().getNss()) - 5 % 10 != 0 && stoi(vecAuxilia[i]->getPropietario().getNss()) - 7 % 10 != 0 ){
                TarjetaVacunacion* tarjVacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(tarjVacunable) {
                    doceCincoSiete.push_back(tarjVacunable);
                }
            }
        }

        cout << "Número de personas: " << doceCincoSiete.size() << endl;
        gestionVacunas.vacunarConjuntoTarjetas(doceCincoSiete,0);

        cout << "\n==== ADMINISTRAR DOSIS A MAYORES DE 25" << endl;

        vector<TarjetaVacunacion*> mayVeinticinco;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            if(vecAuxilia[i]->getPropietario().getEdad() > 25 ){
                TarjetaVacunacion* vacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(vacunable) {
                    mayVeinticinco.push_back(vacunable);
                }
            }
        }
        cout << "Número de personas: " << mayVeinticinco.size() << endl;

        gestionVacunas.vacunarConjuntoTarjetas(mayVeinticinco,0);

        cout << "El porcentaje de usuarios con pauta completa es: " << gestionVacunas.pautaCompleta(0) << " %" << endl;
        cout << "El porcentaje de usuarios con pauta completa en las nuevas condiciones es: " << gestionVacunas.pautaCompleta(1) << " %" << endl;

        cout << "\n==== ADMINISTRAR DOSIS A NIÑOS ENTRE 5 Y 11 AÑOS" << endl;

        int cont  = 0;
        vector<CentroVacunacion*> vecCentros = gestionVacunas.getCentros();
        for (int i = 0; i < vecCentros.size(); ++i){
            vector<TarjetaVacunacion*> usuariosCercanos = vecCentros[i]->buscarCercanos(0.35);
            for(int j = 0; j < usuariosCercanos.size(); ++j) {
                if (usuariosCercanos[j]) {
                    if (usuariosCercanos[j]->getPropietario().getEdad() >= 5 && usuariosCercanos[j]->getPropietario().getEdad() <= 11) {
                        cont++;
                        vecCentros[i]->anadirTarjetaLista(usuariosCercanos[j]);
                        vecCentros[i]->administrarDosis(usuariosCercanos[j],
                                                        usuariosCercanos[j]->getFabricanteRecomendado(1));
                    }
                }
            }
        }
        cout << "Num. de pers: " << cont << endl;
        cout << "\n==== ADMINISTRAR DOSIS A GENTE CON 5 EN ID DE TARJETA" <<  endl;

        cont = 0;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            string str = vecAuxilia[i]->getId();
            bool found = false;
            for (int k = 0; k < str.length() && !found; ++k){
                if (str[k] == '5'){
                    found = true;
                }
            }
            if (found){
                TarjetaVacunacion* vacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(vacunable){
                    cont++;
                CentroVacunacion* centro = gestionVacunas.centroMasCercano(&vacunable->getPropietario());
                    centro->anadirTarjetaLista(vacunable);
                    centro->anadirTarjetaLista(vecAuxilia[i]);
                    centro->administrarDosis(vecAuxilia[i],
                                                    vecAuxilia[i]->getFabricanteRecomendado(1));
                }
            }
        }
        cout << "Num. de pers: " << cont << endl;


        cout << "\n==== ADMINISTRAR DOSIS A MAYORES DE 60" <<  endl;

        cont = 0;
        for (int i = 0; i < vecCentros.size(); ++i){
            vector<TarjetaVacunacion*> usuariosCercanos = vecCentros[i]->buscarCercanos(0.5);
            for(int j = 0; j < usuariosCercanos.size(); ++j) {
                if (usuariosCercanos[j]) {
                    if (usuariosCercanos[j]->getPropietario().getEdad() > 60) {
                        cont++;
                        vecCentros[i]->anadirTarjetaLista(usuariosCercanos[j]);
                        vecCentros[i]->administrarDosis(usuariosCercanos[j],
                                                        usuariosCercanos[j]->getFabricanteRecomendado(1));
                    }
                }
            }
        }
        cout << "Num. de pers: " << cont << endl;

        cont = 0;
        cout << "\n==== VACUNAR AL 90%" <<  endl;

        for (int i = 0; i < vecAuxilia.size() * 0.91; ++i) {
            TarjetaVacunacion *tarjVacunable = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
            if (tarjVacunable) {
                cont++;
                CentroVacunacion *centro = gestionVacunas.centroMasCercano(&tarjVacunable->getPropietario());
                centro->anadirTarjetaLista(tarjVacunable);
                nombreFabricante fab = tarjVacunable->getFabricanteRecomendado(1);
                centro->administrarDosis(tarjVacunable, fab);
            }
        }

        cout << "Num. de pers: " << cont << endl;

        cout << "\n==== FIESTA" <<  endl;
        vector<TarjetaVacunacion*> fiesta;
        for (int i = 0; i < vecAuxilia.size(); ++i){
            if(vecAuxilia[i]->getPropietario().getEdad() == 18){
                TarjetaVacunacion* tarj = gestionVacunas.buscarTarjeta(vecAuxilia[i]);
                if(tarj) {
                    fiesta.push_back(tarj);
                }
            }
        }

        vector<string> avisados = gestionVacunas.avisoColetivo(fiesta,0.075);
        cout << "USUARIOS AVISADOS POR FIESTA: " << avisados.size() << endl;
        //vector<TarjetaVacunacion*> vecAuxilia2;
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}
