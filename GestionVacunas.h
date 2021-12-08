//
// Created by manuel on 28/10/21.
//

#ifndef EEDD_GESTIONVACUNAS_H
#define EEDD_GESTIONVACUNAS_H

#include "Usuario.h"
#include "Dosis.h"
#include <fstream>
#include "CentroVacunacion.h"
#include "THashTarjetaVacunacion.h"
#include <map>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;
class GestionVacunas {

private:
    map<string,Usuario*> listaUsuarios;
    vector<CentroVacunacion*> listaCentros;
    vector<Dosis*> listaDosis;
    vector<string> listaNSS;
    THashTarjetaVacunacion listaTarjetas;
public:
    THashTarjetaVacunacion getListaTarjetas();

private:

    int vacAlmacen;
    int lecturaVacunas;
    int cuantasDosis;
    int cuantosUsuarios;
    vector<int> numVacTipo;
public:
    const string *getFabricantes() const;

public:
    GestionVacunas(); //Constructor por defecto
    GestionVacunas(std::string fileDosis, std::string fileUsuarios, std::string fileCentros);//Constructor parametrizado
    virtual ~GestionVacunas(); //Destructor //arreglao //TODO Composicion de centros
    Usuario *buscarUsuario(string nss); //Busca un usuario en el arbol con el nss //arreglao
    void suministrarNdosisCentro(CentroVacunacion* centro, int numerovacunas);

    vector<string> listadoNSS(); //Listado de los nss de todos los usuarios
    float pautaCompleta(); //Duevuelve el porcentaje de los usuarios con la pauta completa
    vector<Usuario*> listadoVacunacionNR(); //Devuelve los usuarios con la pauta no recomendada
    vector<CentroVacunacion*> getCentros(); //Devuelve los centros de vacunación existentes en el sistema

    const map<string,Usuario*> getListausuarios() const; //devuelve el arbol de usuarios
    int getVacAlmacen() const;
    void setVacAlmacen(int vacAlmacen);
    void printStatus();//devuelve el estado de las vacunas
    void comprobarCorreccionDosis(); // No sale
    const vector<Dosis*> getDosis() const;
    int getPrimeraDosis() const;
    void setPrimeraDosis();
    int getSegundaDosis() const;
    void setSegundaDosis();
    int getTerceraDosis() const;
    void setTerceraDosis();
    int numTotalVacunasTipo(nombreFabricante fabricante); //Devuelve el numero de vacunas disponibles por tipo
    vector<int> getContadoresVacunasTipo(); //Devuelve el numero de vacunas disponibles por tipo
    void sustraerDosisDisponiblesDeContador(nombreFabricante fab);
    CentroVacunacion* centroMasCercano(Usuario* usuario); //Devuelve un puntero al centro de vacunación mas cercano
    std::string getNombreFabricanteDado(nombreFabricante fab); //Devuelve un string del enum de nombrefabricante
    void print();
    void generaTarjetas();

};

#endif //EEDD_GESTIONVACUNAS_H