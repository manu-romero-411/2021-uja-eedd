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
#include "ListaEnlazada.h"
#include "Dosis.h"
#include "Usuario.h"

using namespace std;

int main() {
    ifstream archivoDosis("dosis.txt");
    ifstream archivoUsuarios("usuarios.txt");
    string palabra;
    int corte = 0;

    int id = 0;
    int idLote = 0;
    int fabricante = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;

    clock_t t_ini = clock();

    VDinamico<Dosis> vectorDosis;
    int iterador = 0;
    while (getline(archivoDosis, palabra)) {

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

        //cout << *vectorDosis.leer(iterador);
        ++iterador;
    }
    archivoDosis.close();

    string palabraB;
    corte = 0;
    dia = 0;
    mes = 0;
    anno = 0;
    float longitud, latitud;
    string nombre, apellido, nss;

    ListaEnlazada<int> listaprueba;

    return 0;
    //ListaEnlazada<Usuario> listaUsuarios;
    int iteradorB = 0;
    while (getline(archivoUsuarios, palabraB)) {
        corte = palabraB.find(';');
        nombre = palabraB.substr(0, corte);
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        apellido = palabraB.substr(0, corte);
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        nss =palabraB.substr(0, corte);
        palabraB.erase(0, corte + 1);

        corte = palabraB.find('/');
        dia = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        corte = palabraB.find('/');
        mes = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        anno = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        longitud = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        latitud = stoi(palabraB);

        Usuario nuevoUsuario(nombre,apellido,nss,dia, mes, anno);
        cout << nuevoUsuario << endl;
        ++iteradorB;
    }
    archivoUsuarios.close();
}
  

