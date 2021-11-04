//
// Created by manuel on 28/10/21.
//

#ifndef EEDD_GESTIONVACUNAS_H
#define EEDD_GESTIONVACUNAS_H
#include "ListaEnlazada.h"
#include "VDinamico.h"
#include "Usuario.h"
#include "Dosis.h"

using namespace std;
class GestionVacunas {

private:

    ListaEnlazada<Usuario> listausuarios;
    VDinamico<Dosis> dosis;
    VDinamico<string> listaNSS;
    VDinamico<Usuario> noRecomendados;
public:
GestionVacunas();
GestionVacunas(ListaEnlazada<Usuario>, VDinamico<Dosis>);
GestionVacunas(const ListaEnlazada<Usuario> &usuarios, const VDinamico<Dosis> &dosis);
virtual ~GestionVacunas();
Usuario* buscarUsuario (string nombre);
void administrarDosis(Usuario* vacunando, nombreFabricante vacunada);
bool queAdministro(Usuario* vacunando);
VDinamico<string> listadoNSS();
float pautaCompleta();
VDinamico<Usuario> listadoVacunacionNR();




};


#endif //EEDD_GESTIONVACUNAS_H
