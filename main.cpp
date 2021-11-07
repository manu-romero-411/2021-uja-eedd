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
#include "GestionVacunas.h"

using namespace std;

int main() {
    clock_t t_ini = clock();
    try {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        std::cout << "\n\n**** Instanciación de árbol de enteros ****" << endl;
        AVL<int> arbolPrueba;
        int count = 0;
        int aEncontrar = 0;

        while(count < 1000){
            int ale = (std::rand() % 200000) + 1000;
            if (!(arbolPrueba.buscaIt(ale))){
                arbolPrueba.inserta(ale);
                count++;
                if (count == 535) aEncontrar = ale;
            }
        }
        //AVL<int> otroArbol;
        //otroArbol = arbolPrueba;

        std::cout << "\n\n**** Búsqueda exitosa ****" << endl;
        if (!(arbolPrueba.buscaRec(aEncontrar))){
            std::cout << "* No se ha encontrado " << aEncontrar << std::endl;
        } else {
            std::cout << "* Se ha encontrado " << aEncontrar << std::endl;
        }

        std::cout << "\n\n**** Búsqueda fallida ****" << endl;
        int noTeVoyAencontrarNunca = 14;
        if (!(arbolPrueba.buscaRec(noTeVoyAencontrarNunca))){
            std::cout << "* No se ha encontrado " << noTeVoyAencontrarNunca << std::endl;
        } else {
            std::cout << "* Se ha encontrado " << aEncontrar << std::endl;
        }

        std::cout << "\n\n**** Recorrer en inorden ****" << endl;
        VDinamico<int*> inordenRec = arbolPrueba.recorreInorden();
        for(int i = 0; i < inordenRec.getTamLogico(); ++i){
            int *j = inordenRec[i];
            std::cout << *j << " | ";
        }

        std::cout << "\n\n**** Número de elementos: " << arbolPrueba.getNumElementos() << endl;
        std::cout << "**** Altura: " << arbolPrueba.getAltura() << endl;

        std::cout << std::endl;

        std::cout << "\n\n**** Instanciar usuarios y dosis ****" << endl;
        GestionVacunas gestionVacunas("dosis2.txt", "usuarios2.txt");

        std::cout << "\n\n**** Listado completo de NSS ****" << endl;
        VDinamico<string> vecAuxilia = gestionVacunas.listadoNSS();
        vecAuxilia.print();

        std::cout << "\n\n**** Primera dosis ****" << endl;
        int dosisAdministradas = 0;
        for(int i=0; i<vecAuxilia.getTamLogico();++i){
            if ((stoi(vecAuxilia[i]) % 10) != 0){
                Usuario* encontrado = gestionVacunas.buscarUsuario(vecAuxilia[i]);
                if (encontrado != NULL){
                    bool unaDosis = gestionVacunas.queAdministro(encontrado);
                    dosisAdministradas++;
                }
            }
        }

        std::cout << "Dosis administradas: " << dosisAdministradas << endl;
        std::cout << "\n\n**** Segunda dosis ****" << endl;

        int dosisAdministradas2 = 0;

        for(int i=0; i<vecAuxilia.getTamLogico();++i){
            if (((stoi(vecAuxilia[i]) % 10) != 0) && (((stoi(vecAuxilia[i]) - 3) % 10) != 0)){
                Usuario* encontrado = gestionVacunas.buscarUsuario(vecAuxilia[i]);
                if (encontrado != NULL){
                    bool dosDosis = gestionVacunas.queAdministro(encontrado);
                    dosisAdministradas2++;
                }
            }
        }
        std::cout << "Dosis administradas: " << dosisAdministradas2 << endl;
        std::cout << "\n\n**** Tercera dosis ****" << endl;

        int dosisAdministradas3 = 0;
        for(int i=0; i<vecAuxilia.getTamLogico();++i){
            Usuario* encontrado = gestionVacunas.buscarUsuario(vecAuxilia[i]);
            if (encontrado != NULL) {
                if (encontrado->getedad() >= 75) {
                    if(encontrado->getmisdosis().getTamLogico() == 2) {
                        bool tresDosis = gestionVacunas.queAdministro(encontrado);
                        dosisAdministradas3++;
                    }
                }
            }
        }
        Fecha fecha;
        Usuario prueba("","","1",fecha);
        Dosis dosis(1,1,1,1,1,2001,0);
        Dosis dosis2(1,1,1,1,1,2001,0);

        prueba.nuevaDosis(dosis);
        prueba.nuevaDosis(dosis2);
        std::cout << "Dosis administradas: " << dosisAdministradas3 << endl;
        //AVL<int> *copia = new AVL<int>(arbolPrueba);
        std::cout << "\n\n**** Porcentaje de personas con pauta completa: " << gestionVacunas.pautaCompleta() << " %" << endl;

        std::cout << "\n\n**** Listado de no recomendados ****" << endl;

        std::cout << "\n\n**** Forzar primera dosis de Moderna ****" << endl;
        Usuario* primero = gestionVacunas.buscarUsuario("1622650940");
        gestionVacunas.administrarDosis(primero, Moderna);

        Usuario* segundo = gestionVacunas.buscarUsuario("1941046560");
        gestionVacunas.administrarDosis(segundo, Moderna);

        Usuario* tercero = gestionVacunas.buscarUsuario("1756824615");
        gestionVacunas.administrarDosis(tercero, Moderna);

        Usuario* cuarto = gestionVacunas.buscarUsuario("1625692780");
        gestionVacunas.administrarDosis(cuarto, Moderna);

        Usuario* quinto = gestionVacunas.buscarUsuario("1855345010");
        gestionVacunas.administrarDosis(quinto, Moderna);

        std::cout << std::endl;
        std::cout << "\n\n**** Dosis no administradas: " << gestionVacunas.getVacAlmacen() << endl;

        return 0;
    } catch (std::exception &e) {
        cout << e.what();
        return 1;
    }
}
  

