//
// Created by Manuel Jesús Romero Mateos on 11/11/21.
//

#include "CentroVacunacion.h"
#include "GestionVacunas.h"

CentroVacunacion::CentroVacunacion() {

}

CentroVacunacion::CentroVacunacion(int _id, UTM _direccion) {
    this->id = _id;
    this->direccion = _direccion;
}

void CentroVacunacion::alarmaFaltaDosis(nombreFabricante fab){
    if(numDosisPorFabricante[fab] == 0){
        throw exception(std::underflow_error("No hay vacunas de un fabricante"));
    }
}

void CentroVacunacion::anadirUsuarioLista(Usuario* nuevo){
    listaUsuarios.push_back(nuevo);
}

bool CentroVacunacion::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    int h = 0;
    for(std::map<string,Dosis>::iterator it = listaDosis.begin(); it != listaDosis.end(); ++it) {
        if(it->first==)//TODO
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

void CentroVacunacion::anadirNDosisAlmacen(vector<Dosis> packDosis){
    for(int i = 0; i < packDosis.size(); ++i){
        listaDosis.insert(pair<string,Dosis>(to_string(packDosis[i].getId()), packDosis[i]));
    }
}

int CentroVacunacion::numVacunasTipo(nombreFabricante tipo){
    return numDosisPorFabricante[tipo];
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
