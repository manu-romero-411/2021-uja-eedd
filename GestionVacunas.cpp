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
    bool labuena;
    int edad= vacunando->getedad();

    if(edad>0 && edad<12)
    return false;
    else {
        nombreFabricante laquetoca=vacunando->getdosisRecomendable();
        labuena= administrarDosis(vacunando,laquetoca);
    return labuena;
    }

}


bool GestionVacunas::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    bool noencontrada = true;


    for (int i = 0; i < dosis.getTamLogico() && noencontrada; ++i) {
        if (dosis[i].GetFabricante() == vacunada && dosis[i].getStatus() == enAlmacen) {
            Dosis* p= &dosis[i];
            vacunando->nuevaDosis(*p);
            dosis[i].setStatus(administrada);
            noencontrada = false;
        }

    }
    if (noencontrada) {
        for (int i = 0; i < dosis.getTamLogico() ; ++i) {

            if (dosis[i].getStatus() == enAlmacen && noencontrada) {
                Dosis* p= &dosis[i];
                vacunando->nuevaDosis(*p);
                dosis[i].setStatus(administrada);
                noRecomendados.insertar(vacunando, noRecomendados.getTamLogico());
                noencontrada=false;
                return false;

            }

        }
    }
    return true;
}

float GestionVacunas::pautaCompleta() {
float  numusuarios=this->listausuarios.tam();
float numpautascompletas;
    Iterador<Usuario> itera = this->listausuarios.iteradorInicio();

    for(int i=0; i<listausuarios.tam(); i++){
        if(itera.dato().getmisdosis().getTamLogico()==2){
            numpautascompletas++;
        }

        itera.siguiente();


    }
    numpautascompletas= (numpautascompletas/numusuarios)*100;
    return numpautascompletas;
}

VDinamico<Usuario*> GestionVacunas::listadoVacunacionNR(){
    return noRecomendados;

}


GestionVacunas::~GestionVacunas() {

}
