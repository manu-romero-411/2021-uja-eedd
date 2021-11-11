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
#include "VDinamico.h"
#include "ListaEnlazada.h"
#include "Dosis.h"
#include "Usuario.h"
#include "AVL.h"
#include "GestionVacunas.h"

using namespace std;

int main() {
    try {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        std::cout << "\n**** Instanciación de árbol de enteros ****" << endl;
        AVL<int> arbolPrueba;
        int count = 0;
        int aEncontrar = 0;

        while (count < 1000) {
            int ale = (std::rand() % 200000) + 1000;
            if (!(arbolPrueba.buscaIt(ale))) {
                arbolPrueba.inserta(ale);
                count++;
                if (count == 535) aEncontrar = ale;
            }
        }
        AVL<int> *otroArbol = new AVL<int>(arbolPrueba);
        AVL<int> *otrootroarbol = otroArbol;

        std::cout << "\n**** Búsqueda exitosa ****" << endl;
        if (!(arbolPrueba.buscaRec(aEncontrar))) {
            std::cout << "* No se ha encontrado " << aEncontrar << std::endl;
        } else {
            std::cout << "* Se ha encontrado " << aEncontrar << std::endl;
        }

        std::cout << "\n**** Búsqueda fallida ****" << endl;
        int noTeVoyAencontrarNunca = 14;
        if (!(arbolPrueba.buscaRec(noTeVoyAencontrarNunca))) {
            std::cout << "* No se ha encontrado " << noTeVoyAencontrarNunca << std::endl;
        } else {
            std::cout << "* Se ha encontrado " << aEncontrar << std::endl;
        }

        std::cout << "\n**** Recorrer en inorden ****" << endl;
        VDinamico<int *> inordenRec = arbolPrueba.recorreInorden();
        for (int i = 0; i < inordenRec.getTamLogico(); ++i) {
            int *j = inordenRec[i];
            std::cout << *j << " | ";
        }

        std::cout << "\n**** Número de elementos: " << arbolPrueba.getNumElementos() << endl;
        std::cout << "**** Altura: " << arbolPrueba.getAltura() << endl;

        std::cout << std::endl;

        std::cout << "\n**** Instanciar usuarios y dosis ****" << endl;
        GestionVacunas gestionVacunas("dosis2.txt", "usuarios2.txt");

        std::cout << "\n**** Listado completo de NSS ****" << endl;
        VDinamico<string> vecAuxilia = gestionVacunas.listadoNSS();
        vecAuxilia.print();

        std::cout << "\n**** Primera dosis ****" << endl;
        int dosisAdministradas = 0;
        int adminTot = 0;
        for (int i = 0; i < vecAuxilia.getTamLogico(); ++i) {
            if ((stoi(vecAuxilia[i]) % 10) != 0) {
                Usuario *encontrado = gestionVacunas.buscarUsuario(vecAuxilia[i]);
                if ((encontrado != NULL) && (gestionVacunas.noMenor(encontrado))) {
                    encontrado->tieneDosisRec(gestionVacunas.queAdministro(encontrado));
                    gestionVacunas.setPrimeraDosis();
                }
            }
        }

        std::cout << "Dosis administradas: " << gestionVacunas.getPrimeraDosis() << endl;
        std::cout << "Quedan sin administrar: " << gestionVacunas.getVacAlmacen() << endl;

        std::cout << "\n**** Segunda dosis ****" << endl;

        int dosisAdministradas2 = 0;

        for (int i = 0; i < vecAuxilia.getTamLogico(); ++i) {
            if (((stoi(vecAuxilia[i]) % 10) != 0) && (((stoi(vecAuxilia[i]) - 3) % 10) != 0)) {
                Usuario *encontrado = gestionVacunas.buscarUsuario(vecAuxilia[i]);
                if ((encontrado != NULL) && (gestionVacunas.noMenor(encontrado))) {
                    encontrado->tieneDosisRec(gestionVacunas.queAdministro(encontrado));
                    gestionVacunas.setSegundaDosis();
                }
            }
        }
        std::cout << "Dosis administradas: " << gestionVacunas.getSegundaDosis() << endl;
        std::cout << "Quedan sin administrar: " << gestionVacunas.getVacAlmacen() << endl;
        std::cout << "\n**** Tercera dosis ****" << endl;

        for (int i = 0; i < vecAuxilia.getTamLogico(); ++i) {
            Usuario *encontrado = gestionVacunas.buscarUsuario(vecAuxilia[i]);
            if ((encontrado != NULL) && (gestionVacunas.noMenor(encontrado))) {
                if (encontrado->getedad() >= 75) {
                    if (encontrado->getmisdosis().getTamLogico() == 2) {
                        encontrado->tieneDosisRec(gestionVacunas.queAdministro(encontrado));
                        gestionVacunas.setTerceraDosis();
                    }
                }
            }
        }

        std::cout << "Dosis administradas: " << gestionVacunas.getTerceraDosis() << endl;
        std::cout << "Quedan sin administrar: " << gestionVacunas.getVacAlmacen() << endl;
        std::cout << "\n**** Porcentaje de personas con pauta completa: " << gestionVacunas.pautaCompleta() << " %" << endl;
        std::cout << "\n**** Personas con vacuna no recomendada: " << gestionVacunas.listadoVacunacionNR().getTamLogico() << endl;
        /*if (gestionVacunas.listadoVacunacionNR().getTamLogico() > 0){
            std::cout << "**** Listado de no recomendados ****" << endl;
            gestionVacunas.listadoVacunacionNR().print();
        }*/
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::cout << "\n\n**** Forzar primera dosis de Moderna ****" << endl;
        Usuario* primero = gestionVacunas.buscarUsuario("1622650940");
        if (primero != NULL) gestionVacunas.administrarDosis(primero, Moderna);

        Usuario* segundo = gestionVacunas.buscarUsuario("1941046560");
        if (segundo != NULL) gestionVacunas.administrarDosis(segundo, Moderna);

        Usuario* tercero = gestionVacunas.buscarUsuario("1756824615");
        if (tercero != NULL) gestionVacunas.administrarDosis(tercero, Moderna);

        Usuario* cuarto = gestionVacunas.buscarUsuario("1625692780");
        if (cuarto != NULL) gestionVacunas.administrarDosis(cuarto, Moderna);

        Usuario* quinto = gestionVacunas.buscarUsuario("1855345010");
        if (quinto != NULL) gestionVacunas.administrarDosis(quinto, Moderna);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Diferencia de tiempo 1 = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

        std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
        VDinamico<Usuario> forzados;
        Fecha fecha;
        Usuario nuevoPrimero("","","1622650940",fecha);
        Usuario nuevoSegundo("","","1941046560",fecha);
        Usuario nuevoTercero("","","1756824615",fecha);
        Usuario nuevoCuarto("","","1625692780",fecha);
        Usuario nuevoQuinto("","","1855345010",fecha);

        forzados.insertaFinal(nuevoPrimero);
        forzados.insertaFinal(nuevoSegundo);
        forzados.insertaFinal(nuevoTercero);
        forzados.insertaFinal(nuevoCuarto);
        forzados.insertaFinal(nuevoQuinto);

        for (int i = 0; i < forzados.getTamLogico(); ++i){
            if (gestionVacunas.buscarUsuario(forzados[i].getNss())){
                std::cout << "Usuario forzado " << i+1 << " encontrado " << endl;
            } else {
                std::cout << "Usuario forzado " << i+1 << " no encontrado " << endl;
            }
        }
        std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
        std::cout << "Diferencia de tiempo 2 = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[µs]" << std::endl;
        Usuario *hola = gestionVacunas.buscarUsuario("1492015196");
        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}
  

