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

        cout << "==== Programa de entrenamiento 1 ====" << endl;

        cout << "==== Programa de entrenamiento 2 ====" << endl;

        cout << "*** Instanciación de objetos" << endl;

        cout << "*** Generación de tarjetas de vacunación" << endl;

        cout << "*** Factor de carga de la tabla" << endl;

        cout << "*** Eliminar tarjetas de vacunación de NSS acabados en 0" << endl;

        cout << "*** Número de colisiones máximo producido" << endl;

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