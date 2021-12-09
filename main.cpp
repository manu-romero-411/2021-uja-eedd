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

using namespace std;

int main(int argc, char* argv[]) {
    try {
        Fecha fe;
        fe.asignarDia(1,1,2001);
        UTM ub;
        Usuario us("a","b","0",fe,ub);
        TarjetaVacunacion tar(&us);
        int dos = tar.dosisPorAdministrar();

        cout << "==== Programa de entrenamiento ====" << endl;

        cout << "*** Instanciación de objetos" << endl;
        GestionVacunas gestor(argv[1],argv[2],argv[3]);
        cout << "*** Generación de tarjetas de vacunación" << endl;
        gestor.generaTarjetas();
        cout << "*** Factor de carga de la tabla" << endl;
        float factor = gestor.getListaTarjetas().numTarjetas();
        factor = factor / gestor.getListaTarjetas().tamTabla();
        std::cout<<"Factor de carga: "<<factor <<std::endl;

        cout << "*** Eliminar tarjetas de vacunación de NSS acabados en 0" << endl;

        cout << "*** Número de colisiones máximo producido" << endl;
        int max = gestor.getListaTarjetas().MaximasColisiones();
        int numi = gestor.getListaTarjetas().numTarjetas();
        cout<<max <<std::endl;
        cout << numi << endl;
        cout << "*** Primera dosis a NSS pares" << endl;

        cout << "*** Segunda dosis entre 20 y 50 años" << endl;

        cout << "*** NSS acabados en 2 y 6 sin pauta completa" << endl;

        cout << "*** Reañadir tarjetas de vacunación de NSS acabados en 30" << endl;

        cout << "*** Redispersión" << endl;

        cout << "*** Mostrar usuarios sin pauta recomendada" << endl;

        cout << "*** Diferencia de tiempos" << endl;
        
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}