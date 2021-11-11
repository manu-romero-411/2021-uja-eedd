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
    multimap<string, Dosis>
public:
    CentroVacunacion();
    void alarmaFaltaDosis(nombreFabricante fab);
    void anadirUsuarioLista(Usuario* nuevo);
    bool administrarDosis(Usuario* vacunando, nombreFabricante tipo);
    void anadirNDosisAlmacen(vector<Dosis> packDosis);
    int numVacunasTipo(nombreFabricante tipo);
};


#endif //INC_2021_EEDD_PRACTICAS_CENTROVACUNACION_H
