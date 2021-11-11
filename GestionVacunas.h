//
// Created by manuel on 28/10/21.
//

#ifndef EEDD_GESTIONVACUNAS_H
#define EEDD_GESTIONVACUNAS_H

#include "Usuario.h"
#include "Dosis.h"
#include <fstream>
#include "CentroVacunacion.h"
#include <map>
#include <vector>

using namespace std;
class GestionVacunas {

private:
    map<string,Usuario> listausuarios;
    vector<CentroVacunacion> listacentros;
    vector<Dosis> dosis;
    vector<string> listaNSS;
    vector<Usuario *> noRecomendados;
    int vacAlmacen;
    vector<Dosis> dosisAdministradas;
    vector<bool> dosisAdministradasBin;
    int cuantasDosis;
    int cuantosUsuarios;
    int primeraDosis;
    int segundaDosis;
    int terceraDosis;
public:
    GestionVacunas(); //Constructor por defecto // arreglao
    GestionVacunas(std::string fileDosis, std::string fileUsuarios); //Constructor parametrizado //arreglao
    virtual ~GestionVacunas(); //Destructor //arreglao //TODO Composicion de centros
    Usuario *buscarUsuario(string nss); //Busca un usuario en el arbol con el nss //arreglao
    bool administrarDosis(Usuario *vacunando, nombreFabricante vacunada); //Administra una dosis de un fabricante a un usuario
    bool queAdministro(Usuario *vacunando);//Encuentra la dosis recomendada que administrar a un usuario
    vector<string> listadoNSS(); //Listado de los nss de todos los usuarios
    float pautaCompleta(); //Duevuelve el porcentaje de los usuarios con la pauta completa
    vector<Usuario *> listadoVacunacionNR(); //Devuelve los usuarios con la pauta no recomendada
    const vector<Usuario> &getListausuarios() const; //devuelve el arbol de usuarios
    int getVacAlmacen() const;
    void setVacAlmacen(int vacAlmacen);
    void printStatus();//devuelve el estado de las vacunas
    void comprobarCorreccionDosis(); // No sale
    const vector<Dosis> &getDosis() const; //Devuelve el Vdinamico de las dosis
    int getPrimeraDosis() const;
    void setPrimeraDosis();
    int getSegundaDosis() const;
    void setSegundaDosis();
    int getTerceraDosis() const;
    void setTerceraDosis();
    bool noMenor(Usuario* vacunando);
};

#endif //EEDD_GESTIONVACUNAS_H
