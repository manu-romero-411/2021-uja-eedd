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
    int contNR;
public:
    GestionVacunas();
    GestionVacunas(std::string fileDosis, std::string fileUsuarios);
    virtual ~GestionVacunas();
    Usuario *buscarUsuario(string nombre);
    bool administrarDosis(Usuario *vacunando, nombreFabricante vacunada);
    bool queAdministro(Usuario *vacunando);
    VDinamico<string> listadoNSS();
    float pautaCompleta();
    VDinamico<Usuario *> listadoVacunacionNR();
    const AVL<Usuario> &getListausuarios() const;
    int getVacAlmacen() const;
    void setVacAlmacen(int vacAlmacen);
    void printStatus();
    void comprobarCorreccionDosis();
    const VDinamico<Dosis> &getDosis() const;
    int getPrimeraDosis() const;
    void setPrimeraDosis();
    int getSegundaDosis() const;
    void setSegundaDosis();
    int getTerceraDosis() const;
    void setTerceraDosis();
    bool noMenor(Usuario* vacunando);
};

#endif //EEDD_GESTIONVACUNAS_H
