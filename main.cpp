/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: manuel
 *
 * Created on 22 de septiembre de 2021, 20:36
 */

#include <iostream>
#include <fstream>
#include <string>
#include "VDinamico.h"
#include "Dosis.h"

using namespace std;

int main() {

    ifstream is("dosis.txt");
    string palabra;
    int corte = 0;

    int id = 0;
    int idLote = 0;
    int fabricante = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    std::cout << "hola" <<endl;
            std::cout << "hola" <<endl;
    std::cout << "hola" <<endl;
    std::cout << "hola" <<endl;

    clock_t t_ini = clock();
    VDinamico<Dosis> vectorDosis;

    int iterador = 0;
    while (getline(is, palabra)) {

            corte = palabra.find(';');
            id = stoi(palabra.substr(0, corte));
            palabra.erase(0, corte + 1);

            corte = palabra.find(';');
            idLote = stoi(palabra.substr(0, corte));
            palabra.erase(0, corte + 1);

            corte = palabra.find(';');
            fabricante = stoi(palabra.substr(0, corte));
            palabra.erase(0, corte + 1);

            corte = palabra.find('/');
            dia = stoi(palabra.substr(0, corte));
            palabra.erase(0, corte + 1);

            corte = palabra.find('/');
            mes = stoi(palabra.substr(0, corte));
            palabra.erase(0, corte + 1);

            anno = stoi(palabra);
            Dosis nuevaDosis(id, idLote, fabricante, dia, mes, anno);
            vectorDosis.insertar(nuevaDosis, iterador);

            cout << "Dosis: (ID=" << vectorDosis.leer(iterador)->GetId() 
            << "; Lote=" << vectorDosis.leer(iterador)->GetIdLote()
            << "; Fabricante=\"" << vectorDosis.leer(iterador)->GetFabricante()
            << "\"; Fecha="
            << vectorDosis.leer(iterador)->GetFechaFabricacion().verDia()
            << "/"
            <<vectorDosis.leer(iterador)->GetFechaFabricacion().verMes()
            << "/"
            << vectorDosis.leer(iterador)->GetFechaFabricacion().verAnio()
            << ")" << endl;
            ++iterador;
    }
    /*Dosis *prueba1 = new Dosis(654187074,1,1,1,1,2001);
    Dosis *prueba2 = new Dosis(1,1,1,1,1,2001);
    
    if (*prueba1 > *prueba2) {
        std::cout << "prueba1 mayor que prueba2" << endl;
    } else {
        std::cout << "prueba1 no mayor ni igual que prueba2" << endl;
    }
    
    if (*prueba1 < *prueba2) {
        std::cout << "prueba1 menor que prueba2" << endl;
    } else {
        std::cout << "prueba1 no menor ni igual que prueba2" << endl;
    }
    
    if (*prueba1 == *prueba2) {
        std::cout << "prueba1 igual que prueba2" << endl;
    } else {
        std::cout << "prueba1 no igual que prueba2" << endl;
    }*/
    
    //vectorDosis.ordenar(0,vectorDosis.getTamLogico());
    
    /*for (unsigned i = 0; i < 50; ++i){
        std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i)->GetId() << endl;
    }        

    vectorDosis.ordenarRev()
    for (int i = 0; i < 50; ++i){
        std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i)->GetId() << endl;
    }

    vectorDosis.ordenar()
    for (int i = 0; i < 50; ++i){
        std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i)->GetId() << endl;
    }*/
    
    /*VDinamico<int> prueba223;
    for (int i = 0; i < 100000; i++){
        prueba223.insertar(200000 - i, i);
    }
    
    for (int i = 0; i < 100000; i++){
        std::cout << "  " << *prueba223.leer(i);
    }
    
    std::cout << std::endl;
    int numero = 199;
    
    if (prueba223.busquedaBin(numero,0,9) == -1) {
        std::cout << "no encontrao" << endl;
    }
    for (int i = 0; i < 100000; i++){
        std::cout << "  " << *prueba223.leer(i);
    }
    
    return 0;*/
    
    VDinamico<Dosis> dosisDefectuosas;
    cout << "Vector de dosis: Tamaño lógico " << vectorDosis.getTamLogico() << endl;
    cout << "Vector de defectuosas: Tamaño lógico " << dosisDefectuosas.getTamLogico() << endl;

    int contadorDefect = 0;
    for (int i = 0; i < vectorDosis.getTamLogico(); ++i){
        if(vectorDosis.leer(i)->GetFechaFabricacion().verAnio() == 2020){
            if((vectorDosis.leer(i)->GetIdLote() % 2 == 0) || (vectorDosis.leer(i)->GetIdLote() % 5 == 0)){
                if((vectorDosis.leer(i)->GetId() >= 10000) && (vectorDosis.leer(i)->GetId() <= 2500000)){
                    dosisDefectuosas.insertar(vectorDosis[i], contadorDefect);
                    contadorDefect++;
                    vectorDosis.borrar(i);
                }
            }
        }
    }

    cout << "Vector de dosis: Tamaño lógico " << vectorDosis.getTamLogico() << endl;
    cout << "Vector de defectuosas: Tamaño lógico " << dosisDefectuosas.getTamLogico() << endl;

    for(int i = 0; i < dosisDefectuosas.getTamLogico(); ++i) {
        std::cout << "Dosis defectuosa nº " << i + 1 << ": " << "\n* ID:\t" << dosisDefectuosas.leer(i)->GetId()
                  << "\n* ID Lote:\t";
    }

    cout << "Tiempo lectura: " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs." << endl;
    is.close();
}
