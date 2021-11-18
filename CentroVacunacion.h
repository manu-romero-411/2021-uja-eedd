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
class CentroVacunacion{
private:
    int id;
    UTM direccion;
    list <Usuario*> listaUsuarios;
    multimap<string, Dosis*> listaDosis;
    vector<int> numDosisPorFabricante;
    GestionVacunas* centroGestor;
public:
    CentroVacunacion();
    CentroVacunacion(GestionVacunas* centro, int _id, UTM _direccion);
    void alarmaFaltaDosis(); //Metodo que llama al gestor para pedir nuevas dosis si no quedan
    void anadirUsuarioLista(Usuario* nuevo); //Añade un usuario a la lista de vacunacion
    bool administrarDosis(Usuario* vacunando, nombreFabricante tipo); //Administra una dosis a un usuario
    bool queAdministro(Usuario *vacunando);//Encuentra la dosis recomendada que administrar a un usuario
    void anadirNDosisAlmacen(vector<Dosis*> packDosis); //Añade un vector de dosis a las dosis disponibles en este centro
    int numVacunasTipo(nombreFabricante tipo); //Devuelve el numero de vacunas disponibles de un tipo
    bool noMenor(Usuario* vacunando);
    UTM getUbicacion();
};


#endif //INC_2021_EEDD_PRACTICAS_CENTROVACUNACION_H
