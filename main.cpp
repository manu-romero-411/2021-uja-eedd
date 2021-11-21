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
        Fecha fe;
        fe.asignarDia(1,1,2001);
        UTM ub;
        Usuario us("a","b","0",fe,ub);
        TarjetaVacunacion tar(&us);
        int dos = tar.dosisPorAdministrar();
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}