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

        vectorDosis->insertar(new Dosis(1,1,1,24,03,2020));
       
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
                vectorDosis->insertar(nuevaDosis);

		cout << "Dosis: (ID=" << id << "; Lote=" << idLote << "; Fabricante=\"" << fabricante
		<< "\"; Fecha=" << dia << "/" << mes << "/" << anno << ")" << endl;

	}
 
        char espera;
        for (unsigned i = 0; i < 50; ++i){
            std::cout << "Dosis " << i << ": ID " << vectorDosis->leer()->GetId() << endl;
        }
        std::cin >> espera;
        
        /*
        vectorDosis.ordenarRev();
        for (int i = 0; i < 50; ++i){
            std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i).GetId() << endl;
        }
        std::cin >> espera;
        
        vectorDosis.ordenar();
        for (int i = 0; i < 50; ++i){
            std::cout << "Dosis " << i << ": ID " << vectorDosis.leer(i).GetId() << endl;
        }
        std::cin >> espera;
        
        Dosis dosisBusqueda1(346335905,680,0,24,10,2021);
        Dosis dosisBusqueda2(346335905,680,0,24,10,2021);
        Dosis dosisBusqueda3(346335905,680,0,24,10,2021);
        Dosis dosisBusqueda4(346335905,680,0,24,10,2021);

        int busqueda1 = vectorDosis.busquedaBin(dosisBusqueda1);
        if(busqueda1 == -1){
            std::cout << "No encontrado" << endl;
        }
        
        int busqueda2 = vectorDosis.busquedaBin(dosisBusqueda2);
        if(busqueda2 == -1){
            std::cout << "No encontrado" << endl;
        }
        
        int busqueda3 = vectorDosis.busquedaBin(dosisBusqueda3);
        if(busqueda3 == -1){
            std::cout << "No encontrado" << endl;
        }
        
        int busqueda4 = vectorDosis.busquedaBin(dosisBusqueda4);
        if(busqueda4 == -1){
            std::cout << "No encontrado" << endl;
        }
	is.close();

	cout << "Tiempo lectura: " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs." << endl;
        */
}
