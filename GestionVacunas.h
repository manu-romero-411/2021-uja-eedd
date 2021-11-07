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
    VDinamico<Usuario*> noRecomendados;
    int vacAlmacen;
public:
    int getVacAlmacen() const;

    void setVacAlmacen(int vacAlmacen);

public:
    GestionVacunas();
    GestionVacunas(std::string fileDosis, std::string fileUsuarios) ;
    virtual ~GestionVacunas();
    Usuario* buscarUsuario (string nombre);
    bool administrarDosis(Usuario* vacunando, nombreFabricante vacunada);
    bool queAdministro(Usuario* vacunando);
    VDinamico<string> listadoNSS();
    float pautaCompleta();
    VDinamico<Usuario*> listadoVacunacionNR();
};


#endif //EEDD_GESTIONVACUNAS_H
