/*
 * File:   main.cpp
 * Author: Manuel Jesús Romero Mateos, José Ángel Ángeles Santiago
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

using namespace std;

int main() {
    try {
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

        cout << "\n\n****** Instanciando dosis ******"<< "\n";
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

        cout << "\n\n****** Instanciando usuarios ******"<< "\n";
        ListaEnlazada<Usuario> listaUsuarios;
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
            Fecha fecha;
            fecha.asignarDia(dia,mes,anno);
            Usuario nuevoUsuario(nombre, apellido, nss, fecha, *vectorDosis.leer(iteradorB));
            listaUsuarios.insertaFin(nuevoUsuario);

            //cout << nuevoUsuario << endl;
            ++iteradorB;
        }

        cout << "\n\n****** Mostrando 50 primeros usuarios con el ID de sus dosis ******"<< "\n";
        Iterador<Usuario> iteracao2 = listaUsuarios.iteradorInicio();
        for(int i = 0; i < 50; ++i){
            iteracao2.dato().setMiDosis(*vectorDosis.leer(i));
            cout << iteracao2.dato() << endl;
            iteracao2.siguiente();
        }

        cout << "\n\n****** Buscando NSS de usuarios ******"<< "\n";
        Iterador<Usuario> iteraBusca1 = listaUsuarios.iteradorInicio();
        int anyoActual = 2021;
        int mesActual = 10;
        int diaActual = 19;
        int numUsuario = 0;
        for ( int i = 0; i < listaUsuarios.tam(); ++i){
            if ((iteraBusca1.dato().getNss() == "1491983009") || (iteraBusca1.dato().getNss() == "1280280451") || (iteraBusca1.dato().getNss() == "1696453083")){

                int edad = anyoActual - iteraBusca1.dato().getFechaNacimiento().verAnio();
                if  (iteraBusca1.dato().getFechaNacimiento().verMes() > mesActual) {
                    edad--;
                } else {
                    if ((iteraBusca1.dato().getFechaNacimiento().verDia() > diaActual) && ((iteraBusca1.dato().getFechaNacimiento().verMes() == mesActual))){
                        edad--;
                    }
                }
                cout << "USUARIO " << numUsuario+1 << " -- Nombre: " << iteraBusca1.dato().getNombre()  << " - Apellido: " << iteraBusca1.dato().getApellidos() << " - Edad: " << edad << " años - NSS:"  << iteraBusca1.dato().getNss() << " - ID Dosis:" << iteraBusca1.dato().getMiDosis().GetId() << "\n";
                numUsuario++;
            }
            iteraBusca1.siguiente();
        }

        cout << "\n\n****** Viendo nombres repetidos ******"<< "\n";
        VDinamico<std::string> vectorNombresRepes;
        Iterador<Usuario> iteraBusca3 = listaUsuarios.iteradorInicio();

        for (int i = 0; i < listaUsuarios.tam(); ++i){
            vectorNombresRepes.insertar(iteraBusca3.dato().getNombre(),i);
            iteraBusca3.siguiente();
        }
        
        vectorNombresRepes.ordenar();

        std::string nombreRepetido = *vectorNombresRepes.leer(0);
        int vecesRepetido = 1;
        int mayorVecesRepetido = 1;
        for (int i = 1; i < vectorNombresRepes.getTamLogico(); i++){
            std::string nombreActual = *vectorNombresRepes.leer(i);
            std::string nombreAnterior = *vectorNombresRepes.leer(i-1);
            if (nombreActual == nombreAnterior){
                vecesRepetido++;
                if (vecesRepetido > mayorVecesRepetido) {
                    mayorVecesRepetido = vecesRepetido;
                    nombreRepetido = *vectorNombresRepes.leer(i);
                }
            } else {
                vecesRepetido = 1;
            }
        }
        cout << "Nombre más repetido: " << nombreRepetido << " (" << mayorVecesRepetido << " veces) \n" ;

        cout << "\n\n****** Buscando y borrando usuarios Joan ******"<< "\n";
        cout << "\nNúmero de usuarios antes de borrar Joan: "<< listaUsuarios.tam() << "\n";

        Iterador<Usuario> iteraBusca2 = listaUsuarios.iteradorInicio();
        int numJoan = 0;
        for (int i = 0; i < listaUsuarios.tam(); ++i) {
            if (iteraBusca2.dato().getNombre() == "Joan"){
                numJoan++;
                listaUsuarios.borra(iteraBusca2);
                //cout << "Borrado Joan nº" << numJoan << "\n";
            }
            iteraBusca2.siguiente();
        }
        cout << "Número de Joan borrados: " << numJoan << "\n";
        cout << "Número de usuarios tras borrar Joan: "<< listaUsuarios.tam() << "\n";

        Iterador<Usuario> iteraBusca4 = listaUsuarios.iteradorInicio();
        numJoan = 0;
        for (int i = 0; i < listaUsuarios.tam(); ++i) {
            if (iteraBusca4.dato().getNombre() == "Joan"){
                numJoan++;
                listaUsuarios.borra(iteraBusca2);
                //cout << "Borrado Joan nº" << numJoan << "\n";
            }
            iteraBusca4.siguiente();
        }
        cout << "Número de Joan encontrados después: "<<  numJoan << "\n";

        //cout << "Resultado de volver a buscar Joan: " <<

        archivoUsuarios.close();
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}
  

