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

void CentroVacunacion::alarmaFaltaDosis(){
    GestionVacunas::suminitrarNdosis


}

void CentroVacunacion::anadirUsuarioLista(Usuario* nuevo){
    listaUsuarios.push_back(nuevo);
}

bool CentroVacunacion::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    if(listaDosis.size()<=0)
        alarmaFaltaDosis();
    bool encontrado = false;
    for (std::list<Usuario *>::iterator it1 = listaUsuarios.begin(); it1 != listaUsuarios.end(); ++it1) {
        if (*it1 == vacunando) {
            encontrado = true;
        }
    }
        if (encontrado) {
            bool vacunado = false;

            for (std::map<string, Dosis>::iterator it2 = listaDosis.begin(); it2 != listaDosis.end(); ++it2) {
                std::string nombrevacunada = std::to_string(nombreFabricante(vacunada));
                if (it2->first == nombrevacunada && it2->second.getStatus() == enAlmacen) {//TODO
                    vacunando->nuevaDosis(&it2->second);
                    it2->second.setStatus(administrada);
                    listaUsuarios.remove(vacunando);
                    vacunado = true;
                    return true;
                }
            }
                if (vacunado == false) {
                    for (std::map<string, Dosis>::iterator it2 = listaDosis.begin(); it2 != listaDosis.end(); ++it2) {
                        if (it2->second.getStatus() == enAlmacen) {
                            vacunando->nuevaDosis(&it2->second);
                            it2->second.setStatus(administrada);
                            listaUsuarios.remove(vacunando);
                            vacunado = true;
                            return true;
                        }
                    }
                }

            return true;
        }


        else return false;
}

void CentroVacunacion::anadirNDosisAlmacen(vector<Dosis> packDosis){
    for(int i = 0; i < packDosis.size(); ++i){
        Dosis* nueva = &packDosis[i];
        listaDosis.insert(pair<string,Dosis>(nueva->getnombrefabricante(), *nueva));

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
