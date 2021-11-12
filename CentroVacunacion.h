//
// Created by Manuel Jesús Romero Mateos on 11/11/21.
//

#ifndef INC_2021_EEDD_PRACTICAS_CENTROVACUNACION_H
#define INC_2021_EEDD_PRACTICAS_CENTROVACUNACION_H

#include <map>
#include <cstdlib>
#include "UTM.h"
#include "Dosis.h"
#include "Usuario.h"
#include <list>

class GestionVacunas;
class CentroVacunacion {
private:
    int id;
    UTM direccion;
    list <Usuario*> listaUsuarios;
    multimap<string, Dosis> listaDosis;
public:
    CentroVacunacion();
    void alarmaFaltaDosis(nombreFabricante fab);
    void anadirUsuarioLista(Usuario* nuevo);
    bool administrarDosis(Usuario* vacunando, nombreFabricante tipo);
    bool queAdministro(Usuario *vacunando);//Encuentra la dosis recomendada que administrar a un usuario
    void anadirNDosisAlmacen(vector<Dosis> packDosis);
    int numVacunasTipo(nombreFabricante tipo);
    bool noMenor(Usuario* vacunando);
};


#endif //INC_2021_EEDD_PRACTICAS_CENTROVACUNACION_H
