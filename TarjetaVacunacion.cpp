//
// Created by Manuel Jesús Romero Mateos on 18/11/21.
//

#include "TarjetaVacunacion.h"

TarjetaVacunacion::TarjetaVacunacion() {}

TarjetaVacunacion::TarjetaVacunacion(Usuario* _usuario) {
    this->propietario = _usuario;
    string _id = _usuario->getNss();
    _id.append(_usuario->getNombre());
    this->id = _id;
    this->pautaRecomendada = false;
    this->pautaCompleta = false;
}

Dosis& TarjetaVacunacion::getDosis(int cual){
    if(cual < dosisAdministradas.size()) {
        return *dosisAdministradas[cual];
    }
    else
        throw std::out_of_range("[Usuario] Posición no valida al llamar a VDinamico<Dosis>");
}

void TarjetaVacunacion::nuevaDosis(Dosis* nueva){
    Dosis* p= nueva;
    dosisAdministradas.push_back(p);
    p->setStatus(administrada);
}

vector<Dosis*> TarjetaVacunacion::getDosisAdministradas(){
    return dosisAdministradas;
}

nombreFabricante TarjetaVacunacion::getFabricanteRecomendado(){
    if (propietario->getedad() >= 12 && propietario->getedad() < 30)
        return Johnson;
    if (propietario->getedad() >= 30 && propietario->getedad() < 50)
        return AstraZeneca;
    if (propietario->getedad() >= 50 && propietario->getedad() < 65)
        return Moderna;
    if (propietario->getedad() >= 65)
        return Pfizer;
    if (propietario->getedad() < 12)
        return ninguno;
}

bool TarjetaVacunacion::isDosisRec(){
    return pautaRecomendada;
}

void TarjetaVacunacion::tieneDosisRec(bool rec){
    pautaRecomendada = rec;
}

int TarjetaVacunacion::dosisPorAdministrar(){
    if (propietario->getedad() >= 75) return 3 - dosisAdministradas.size();
    if (propietario->getedad() < 12) return 0;
    if (propietario->getedad() >= 12 && propietario->getedad() < 75) return 2 - dosisAdministradas.size();
}

Usuario& TarjetaVacunacion::getPropietario(){
    return *propietario;
}

const string &TarjetaVacunacion::getId() const {
    return id;
}

void TarjetaVacunacion::setId(const string &id) {
    TarjetaVacunacion::id = id;
}

bool TarjetaVacunacion::isPautaCompleta() const {
    return pautaCompleta;
}

void TarjetaVacunacion::setPautaCompleta(bool pautaCompleta) {
    TarjetaVacunacion::pautaCompleta = pautaCompleta;
}

int TarjetaVacunacion::getIdCentroCercano() const {
    return idCentroCercano;
}

void TarjetaVacunacion::setIdCentroCercano(int idCentroCercano) {
    TarjetaVacunacion::idCentroCercano = idCentroCercano;
}

bool TarjetaVacunacion::isPautaRecomendada() const {
    return pautaRecomendada;
}

void TarjetaVacunacion::setPautaRecomendada(bool pautaRecomendada) {
    TarjetaVacunacion::pautaRecomendada = pautaRecomendada;
}

const vector<Dosis *> &TarjetaVacunacion::getDosisAdministradas() const {
    return dosisAdministradas;
}

string TarjetaVacunacion::pasaporteCovidCode(){


}

bool TarjetaVacunacion::operator==(const TarjetaVacunacion &ladeladerecha) {
    return (this->id == ladeladerecha.id);
}

 TarjetaVacunacion::~TarjetaVacunacion(){}
