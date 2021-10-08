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
    
    // Ordenación de dosis
    std::cout << "\n\n***Dosis sin ordenar:\n";
    for (unsigned i = 0; i < 50; ++i){
        std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i)->GetId() << endl;
    }        
    
    std::cout << "\n\n***Dosis ordenadas al revés:\n";
    vectorDosis.ordenarRev();
    for (int i = 0; i < 50; ++i){
        std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i)->GetId() << endl;
    }

    std::cout << "\n\n***Dosis ordenadas de menor a mayor:\n";
    vectorDosis.ordenar();
    for (int i = 0; i < 50; ++i){
        std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i)->GetId() << endl;
    }
    
    // Búsqueda de dosis
    Dosis dosisbusq1(346335905);
    Dosis dosisbusq2(999930245);
    Dosis dosisbusq3(165837);
    Dosis dosisbusq4(486415569);
    Dosis dosisbusq5(61385551);
    
    int busq1=vectorDosis.busquedaBin(dosisbusq1,0,vectorDosis.getTamLogico());
    if(busq1==-1)
        cout<<"Dosis " << dosisbusq1.GetId() << " no encontrada \n";
    else   
        cout<<"Dosis " << dosisbusq1.GetId() << " encontrada en la posición " << busq1 << "\n";
    
    int busq2=vectorDosis.busquedaBin(dosisbusq2,0,vectorDosis.getTamLogico());
    if(busq2==-1)
        cout<<"Dosis " << dosisbusq2.GetId() << " no encontrada \n";
    else   
        cout<<"Dosis " << dosisbusq2.GetId() << " encontrada en la posición " << busq2 << "\n";
    
    int busq3=vectorDosis.busquedaBin(dosisbusq3,0,vectorDosis.getTamLogico());
    if(busq3==-1)
        cout<<"Dosis " << dosisbusq3.GetId() << " no encontrada \n";
    else   
        cout<<"Dosis " << dosisbusq3.GetId() << " encontrada en la posición " << busq3 << "\n";
    
    int busq4=vectorDosis.busquedaBin(dosisbusq4,0,vectorDosis.getTamLogico());
    if(busq4==-1)
        cout<<"Dosis " << dosisbusq4.GetId() << " no encontrada \n";
    else   
        cout<<"Dosis " << dosisbusq4.GetId() << " encontrada en la posición " << busq4 << "\n";
    
    int busq5=vectorDosis.busquedaBin(dosisbusq5,0,vectorDosis.getTamLogico());
    if(busq5==-1)
        cout<<"Dosis " << dosisbusq5.GetId() << " no encontrada \n";
    else   
        cout<<"Dosis " << dosisbusq5.GetId() << " encontrada en la posición " << busq5 << "\n";
    
    //Dosis defectuosas
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
    
  return 0;

    }
  

