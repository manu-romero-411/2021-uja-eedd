//
// Created by Manuel Jesús Romero Mateos on 11/11/21.
//

#include "CentroVacunacion.h"
#include "GestionVacunas.h"

CentroVacunacion::CentroVacunacion() {

}

void CentroVacunacion::alarmaFaltaDosis(nombreFabricante fab){

}

void CentroVacunacion::anadirUsuarioLista(Usuario* nuevo){

}

bool CentroVacunacion::administrarDosis(Usuario* vacunando, nombreFabricante tipo){
    bool GestionVacunas::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
        int h = 0;
        for (int i = 0; i < dosisAdministradasBin.size(); ++i){
            Dosis *esta = &dosis[i];
            vacunando->nuevaDosis(esta);
            esta->setStatus(administrada);
            vacAlmacen--;
            h = i;
            dosisAdministradasBin[i] = true;
            return true;
        }


        comprobarCorreccionDosis();
        int j = 0;
        while (dosis[j].getStatus() != enAlmacen){
            j++;
        }
        if (j < dosis.size()){
            Dosis* esta = &dosis[j];
            vacunando->nuevaDosis(esta);
            dosis[j].setStatus(administrada);
            noRecomendados.insertaFinal(vacunando);
            vacAlmacen--;
        }
        return false;

    }

}

void CentroVacunacion::anadirNDosisAlmacen(vector<Dosis> packDosis){

}

int CentroVacunacion::numVacunasTipo(nombreFabricante tipo){

}

bool CentroVacunacion::queAdministro(Usuario *vacunando) {
    bool labuena;
    int edad = vacunando->getedad();

    if(!noMenor(vacunando)) return false;
    else {
        nombreFabricante laquetoca = vacunando->getdosisRecomendable();
        labuena = administrarDosis(vacunando,laquetoca);
        return labuena;
    }
}

bool CentroVacunacion::noMenor(Usuario* vacunando){
    if(vacunando->getedad() > 0 && vacunando->getedad() < 12) return false;
    else return true;
}
