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
#include "RandomPrimeGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        cout << "hola" << endl;
        Fecha f(1,1,2001,1,1);
        UTM ub(37,-3);
        Usuario* u = new Usuario("a","b","1",f,ub);
        TarjetaVacunacion* a = new TarjetaVacunacion(u);
        THashTarjetaVacunacion* tabla = new THashTarjetaVacunacion(10000);
        tabla->insertar(1,*a);
        if (tabla->buscar(1,*a)) cout << "si" << endl;
        string idd = a->getId();
        tabla->borrar(1, idd);
        tabla->insertar(1,*a);
        tabla->insertar(2,*a);
        tabla->borrar(2,idd);

        THashTarjetaVacunacion* tabla2 = tabla;
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}