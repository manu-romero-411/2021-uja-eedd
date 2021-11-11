//
// Created by manuel on 28/10/21.
//

#ifndef EEDD_GESTIONVACUNAS_H
#define EEDD_GESTIONVACUNAS_H

#include "ListaEnlazada.h"
#include "VDinamico.h"
#include "Usuario.h"
#include "Dosis.h"
#include "AVL.h"
#include <fstream>

using namespace std;
class GestionVacunas {

private:
    AVL<Usuario> listausuarios;
    VDinamico<Dosis> dosis;
    VDinamico<string> listaNSS;
    VDinamico<Usuario *> noRecomendados;
    int vacAlmacen;
    VDinamico<Dosis> dosisAdministradas;
    int cuantasDosis;
    int cuantosUsuarios;
    int primeraDosis;
    int segundaDosis;
    int terceraDosis;
public:
    GestionVacunas(); //Constructor por defecto
    GestionVacunas(std::string fileDosis, std::string fileUsuarios); //Constructor parametrizado
    virtual ~GestionVacunas(); //Destructor
    Usuario *buscarUsuario(string nss); //Busca un usuario en el arbol con el nss
    bool administrarDosis(Usuario *vacunando, nombreFabricante vacunada); //Administra una dosis de un fabricante a un usuario
    bool queAdministro(Usuario *vacunando);//Encuentra la dosis recomendada que administrar a un usuario
    VDinamico<string> listadoNSS(); //Listado de los nss de todos los usuarios
    float pautaCompleta(); //Duevuelve el porcentaje de los usuarios con la pauta completa
    VDinamico<Usuario *> listadoVacunacionNR(); //Devuelve los usuarios con la pauta no recomendada
    const AVL<Usuario> &getListausuarios() const; //devuelve el arbol de usuarios
    int getVacAlmacen() const;
    void setVacAlmacen(int vacAlmacen);
    void printStatus();//devuelve el estado de las vacunas
    void comprobarCorreccionDosis(); // No sale
    const VDinamico<Dosis> &getDosis() const; //Devuelve el Vdinamico de las dosis
    int getPrimeraDosis() const;
    void setPrimeraDosis();
    int getSegundaDosis() const;
    void setSegundaDosis();
    int getTerceraDosis() const;
    void setTerceraDosis();
    bool noMenor(Usuario* vacunando);
};

#endif //EEDD_GESTIONVACUNAS_H
