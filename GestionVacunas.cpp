//
// Created by manuel on 28/10/21.
//

#include "GestionVacunas.h"




GestionVacunas::GestionVacunas(const ListaEnlazada<Usuario> &usuarios, const VDinamico<Dosis> &dosis) : listausuarios(
        usuarios), dosis(dosis)
        {}


Usuario* GestionVacunas::buscarUsuario (string nss){
    Iterador<Usuario> itera = this->listausuarios.iteradorInicio();

    for(int i=0; i<listausuarios.tam(); i++){
        if(itera.dato().getNss()==nss)
        return &itera.dato();
    itera.siguiente();
    }
return nullptr;

}
bool GestionVacunas::queAdministro(Usuario *vacunando) {
    int edad= vacunando->getedad();

    if(edad>0 && edad<12)
    return false;
    else {
        if (edad >= 12 && edad < 30)
            administrarDosis(vacunando, Johnson);
        if (edad >= 30 && edad < 50)
            administrarDosis(vacunando, AstraZeneca);
        if (edad >= 50 && edad < 65)
            administrarDosis(vacunando, Moderna);
        if (edad >= 65)
            administrarDosis(vacunando, Pfizer);
    return true;
    }

}


void GestionVacunas::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    bool noencontrada = true;


    for (int i = 0; i < dosis.getTamLogico() && noencontrada; ++i) {
        if (dosis[i].GetFabricante() == vacunada && dosis[i].getStatus() == enAlmacen) {
            vacunando->nuevaDosis(dosis[i]);
            dosis[i].setStatus(administrada);
            noencontrada = false;
        }

    }
    if (noencontrada) {
        for (int i = 0; i < dosis.getTamLogico() && noencontrada; ++i) {
            if (dosis[i].getStatus() == enAlmacen) {
                vacunando->nuevaDosis(dosis[i]);
                dosis[i].setStatus(administrada);
                noRecomendados.insertar(*vacunando, noRecomendados.getTamLogico());

            }

        }
    } else

}

GestionVacunas::~GestionVacunas() {

}
