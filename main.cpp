/*
 * File:   main.cpp
 * Author: Manuel Jesus Romero Mateos, Jose angel angeles Santiago
 *
 * Created on 22 de septiembre de 2021, 20:36
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "VDinamico.h"
#include "ListaEnlazada.h"
#include "Dosis.h"
#include "Usuario.h"
#include "AVL.h"

using namespace std;

int main() {
    try {
        AVL<int> arbolPrueba;

        AVLNodo<int>* elnodo = arbolPrueba.getNodoRaiz();
        int h=1;
        int ii=2;
        int iii=3;
        int iv=4;
        int v=5;
        int vi=6;
        int vii=7;
        int viii=8;
        int ix=9;
        int x=10;
        int menosx=-10;
        int menosiv=-4;
        arbolPrueba.inserta(ii);
        arbolPrueba.inserta(h);
        arbolPrueba.inserta(iii);
        arbolPrueba.inserta(menosiv);
        int altura =  arbolPrueba.getAltura();
        AVL<int> prueba;
        prueba = arbolPrueba;
        int num = arbolPrueba.getNumElementos();
        //AVLNodo<int> busca = arbolPrueba.getNodoRaiz();
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}
  

