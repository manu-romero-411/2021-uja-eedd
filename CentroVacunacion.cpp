//
// Created by Manuel Jesús Romero Mateos on 11/11/21.
//

#include "CentroVacunacion.h"
#include "GestionVacunas.h"
#include "Dosis.h"

CentroVacunacion::CentroVacunacion() {

}
/**
* @brief Constructor por defecto
* @param[in] Puntero al gestor, id del centro, su dirección
* @param[out] -
* @return -
*
*
*/
CentroVacunacion::CentroVacunacion(GestionVacunas* centro, int _id, UTM _direccion) {
    this->centroGestor = centro;
    this->id = _id;
    this->direccion = _direccion;
}
/**
* @brief Metodo que llama al gestor para pedir nuevas dosis si no quedan dosis
* @param[in]
* @param[out] -
* @return -
*
*
*/
void CentroVacunacion::alarmaFaltaDosis(){
    if(listaDosis.size() <= 0)
        centroGestor->suministrarNdosisCentro(this,100);
}
/**
* @brief Añade un usuario a la lista de vacunación
* @param[in] Usuario que añadir
* @param[out] -
* @return -
*
*
*/
void CentroVacunacion::anadirUsuarioLista(Usuario* nuevo){
    bool esta = false; //Comprobación si el usuario ya está en el vector
    for (std::list<Usuario*>::iterator it1 = listaUsuarios.begin(); it1 != listaUsuarios.end() && !esta; ++it1) {
        if (*it1 == nuevo) {
            esta = true;
            break;
        }
    }

    if (!(esta)){
        listaUsuarios.push_back(nuevo);
    }
}
/**
* @brief Administra una dosis a un usuario
* @param[in] Usuario que vacunar, tipo de dosis recomendada
* @param[out] -
* @return -
*
*
*/
bool CentroVacunacion::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    if (listaDosis.size() <= 0){
        cout << "Vector de dosis en un CentroVacunacion es de tamaño 0. Alarma lanzada" << endl;
        alarmaFaltaDosis();
    }
    
    bool encontrado = false;
    for (std::list<Usuario*>::iterator it1 = listaUsuarios.begin(); it1 != listaUsuarios.end(); ++it1) {
        if (*it1 == vacunando) {
            encontrado = true;
        }
    }

    if (encontrado) {
        bool vacunado = false;

        for (std::map<string, Dosis*>::iterator it2 = listaDosis.begin(); it2 != listaDosis.end(); ++it2) {
            std::string nombrevacunada = centroGestor->getNombreFabricanteDado(vacunada);
            if (it2->first == nombrevacunada && it2->second->getStatus() == enAlmacen) {//TODO
                vacunando->nuevaDosis(it2->second);
                it2->second->setStatus(administrada);
                vacunando->tieneDosisRec(true);
                listaUsuarios.remove(vacunando);
                listaDosis.erase(it2);

                centroGestor->sustraerDosisDisponiblesDeContador(vacunada); // Con esto le restamos uno al contador de vacunas en almacén de x tipo
                //vacunado = true;
                return true;
            }
        }
        if (vacunado == false) {
            for (std::map<string, Dosis*>::iterator it2 = listaDosis.begin(); it2 != listaDosis.end(); ++it2) {
                if (it2->second->getStatus() == enAlmacen) {
                    vacunando->nuevaDosis(it2->second);
                    it2->second->setStatus(administrada);
                    vacunando->tieneDosisRec(false);
                    listaUsuarios.remove(vacunando);
                    centroGestor->sustraerDosisDisponiblesDeContador(vacunada); // Con esto le restamos uno al contador de vacunas en almacén de x tipo
                    listaDosis.erase(it2);
                    //vacunado = true;
                    return true;
                }
            }
        }
        return true;
    } else return false;
}
/**
* @brief Añade nuevas dosis a las dosis disponibles
* @param[in] vector con nuevas dosis
* @param[out] -
* @return -
*
*
*/
void CentroVacunacion::anadirNDosisAlmacen(vector<Dosis*> packDosis){
    for(int i = 0; i < packDosis.size(); ++i){
        Dosis* nueva = packDosis[i];
        listaDosis.insert(pair<string,Dosis*>(nueva->getnombrefabricante(), nueva));
    }
}

int CentroVacunacion::numVacunasTipo(nombreFabricante tipo){
    return numDosisPorFabricante[tipo];
}
/**
* @brief Encuentra la dosis recomendada que administrar a un usuario
* @param Usuario al que vacunar
* @param[out] -
* @return -
*
*
*/
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

UTM CentroVacunacion::getUbicacion(){
    return direccion;
}
