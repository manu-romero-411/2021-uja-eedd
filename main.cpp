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

int main() {
    try {
        GestionVacunas gestionVacunas;

        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}
  

