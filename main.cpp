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
        VDinamico<Dosis> vectorDosis();
	clock_t t_ini = clock();

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
                vectorDosis->insertar(nuevaDosis, i);
                ++i;
		cout << "Dosis: (ID=" << id << "; Lote=" << idLote << "; Fabricante=\"" << fabricante
		<< "\"; Fecha=" << dia << "/" << mes << "/" << anno << ")" << endl;

	}
 
        for (unsigned i = 0; i < 50; ++i){
            std::cout << "Dosis " << i << ": ID " << vectorDosis->leer()->GetId() << endl;
        }        
       
        vectorDosis.ordenarRev();
        for (int i = 0; i < 50; ++i){
            std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i).GetId() << endl;
        }
        
        vectorDosis.ordenar();
        for (int i = 0; i < 50; ++i){
            std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i).GetId() << endl;
        }
        
        Dosis dosisBusqueda1(346335905,680,0,24,10,2021);
        Dosis dosisBusqueda2(999930245,680,0,24,10,2021);
        Dosis dosisBusqueda3(165837,680,0,24,10,2021);
        Dosis dosisBusqueda4(61385551,680,0,24,10,2021);

        int busqueda1 = vectorDosis.busquedaBin(dosisBusqueda1);
        if(busqueda1 == -1){
            std::cout << "No encontrado" << endl;
        } else {
            std::cout << "Encontrado 346335905 en posición" << busqueda1 << endl;
        }
        
        int busqueda2 = vectorDosis.busquedaBin(dosisBusqueda2);
        if(busqueda2 == -1){
            std::cout << "No encontrado" << endl;
         } else {
            std::cout << "Encontrado 999930245 en posición" << busqueda2 << endl;
        }
        
        int busqueda3 = vectorDosis.busquedaBin(dosisBusqueda3);
        if(busqueda3 == -1){
            std::cout << "No encontrado" << endl;
         } else {
            std::cout << "Encontrado 165837 en posición" << busqueda3 << endl;
        }
        
        int busqueda4 = vectorDosis.busquedaBin(dosisBusqueda4);
        if(busqueda4 == -1){
            std::cout << "No encontrado" << endl;
         } else {
            std::cout << "Encontrado 61385551 en posición" << busqueda4 << endl;
        }
        
	is.close();
        VDinamico<Dosis> dosisDefectuosas = new VDinamico<Dosis>();
        
        cout << "Vector de dosis: Tamaño lógico " << vectorDosis.getTamLogico() << endl;
        cout << "Vector de defectuosas: Tamaño lógico " << dosisDefectuosas.getTamLogico() << endl;
        
        int contadorDefect = 0;
        for (int i = 0; i < vectorDosis.getTamLogico(); ++i){
            if((vectorDosis.leer(i)->GetId() >= 10000) && (vectorDosis.leer(i)->GetId() >= 2500000)){
                if((vectorDosis.leer(i)->GetIdLote() % 2 == 0) || (vectorDosis.leer(i)->GetIdLote() % 5 == 0)){
                    if(vectorDosis.leer(i)->GetFechaFabricacion().verAnio() == 2020){
                        dosisDefectuosas.insertar(vectorDosis.leer(i), contadorDefect);
                        contadorDefect++;
                        vectorDosis.borrar(i);
                    }
                }
            }
        }
        
        cout << "Vector de dosis: Tamaño lógico " << vectorDosis.getTamLogico() << endl;
        cout << "Vector de defectuosas: Tamaño lógico " << dosisDefectuosas.getTamLogico() << endl;

        for(int i = 0; i < 5; ++i){
            std::cout << "Dosis defectuosa nº " << i+1 << ": " << "\n* ID:\t" << dosisDefectuosas.leer(i)->GetId() <<  "\n* ID Lote:\t" <<
        }
        
        
	cout << "Tiempo lectura: " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs." << endl;
        
}
