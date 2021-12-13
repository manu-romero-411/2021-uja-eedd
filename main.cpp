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
#include "img.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        GestionVacunas* gestionVacunas = new GestionVacunas(argv[1],argv[2],argv[3]);
        gestionVacunas->generaTarjetas();
        RGBColor color('1','2','3');
        Img img(200,200,color);
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}