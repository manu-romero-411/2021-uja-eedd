//
// Created by Manuel Jesús Romero Mateos on 18/11/21.
//

#include "TarjetaVacunacion.h"
#include "picosha2.h"

TarjetaVacunacion::TarjetaVacunacion()  {

    this->id = "0";
    this->pautaCompleta = false;
    this->idCentroCercano = 0;
    this->pautaRecomendada = false;
    this->propietario = nullptr;
}

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
        throw std::out_of_range("[Usuario] Posición no valida al llamar a vector<Dosis>");
}

void TarjetaVacunacion::nuevaDosis(Dosis* nueva){
    Dosis* p= nueva;
    dosisAdministradas.push_back(p);
    p->setStatus(administrada);
    this->isCompleta();
}

vector<Dosis*> TarjetaVacunacion::getDosisAdministradas(){
    return dosisAdministradas;
}

nombreFabricante TarjetaVacunacion::getFabricanteRecomendado(){
    if (propietario->getEdad() >= 12 && propietario->getEdad() < 30)
        return Johnson;
    if (propietario->getEdad() >= 30 && propietario->getEdad() < 50)
        return AstraZeneca;
    if (propietario->getEdad() >= 50 && propietario->getEdad() < 65)
        return Moderna;
    if (propietario->getEdad() >= 65)
        return Pfizer;
    if (propietario->getEdad() < 12)
        return ninguno;
}

bool TarjetaVacunacion::isDosisRec(){
    return pautaRecomendada;
}

void TarjetaVacunacion::tieneDosisRec(bool rec){
    pautaRecomendada = rec;
}

int TarjetaVacunacion::dosisPorAdministrar(){
    if (propietario->getEdad() >= 75) return 3 - dosisAdministradas.size();
    if (propietario->getEdad() < 12) return 0;
    if (propietario->getEdad() >= 12 && propietario->getEdad() < 75) return 2 - dosisAdministradas.size();
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

string TarjetaVacunacion::pasaporteCovidCode(bool &valido){
    if (this->pautaRecomendada){
        std::string hash_hex_str;
        std::string h = (id
                         + getNombreFabricanteDado(nombreFabricante(getDosisAdministradas()[0]->getFabricante()))
                         + to_string(getDosisAdministradas().size()));
        picosha2::hash256_hex_string(h,
        hash_hex_str); // ESTA FUNCIÓN ES LA QUE NOS PERMITE SABER EL HASH DE CADA PASAPORTE COVID
        valido = true;
        return hash_hex_str;
    } else {
        string hashVacio;
        picosha2::hash256_hex_string("",hashVacio);
        valido = false; //Valido es un parametro para ver si se ha hecho el pasaporte o no
        return hashVacio;
    }
}

bool TarjetaVacunacion::operator==(const TarjetaVacunacion &ladeladerecha) {
    return (this->id == ladeladerecha.id);
}

TarjetaVacunacion::~TarjetaVacunacion(){}

void TarjetaVacunacion::isCompleta() {
    if (propietario->getEdad() > 12 && propietario->getEdad() < 75)
        if (dosisAdministradas.size() == 2) {
            setPautaCompleta(true);
        }
    if (propietario->getEdad() > 75) {
        if (dosisAdministradas.size() == 3) {
            setPautaCompleta(true);
        }
    }
}

std::string TarjetaVacunacion::getNombreFabricanteDado(nombreFabricante fab){
    switch(fab) {
        case (0):
            return "Pfizer";
            break;
        case (1):
            return "Moderna";
            break;
        case (2):
            return "AstraZeneca";
            break;
        case (3):
            return "Johnson";
            break;
    }
}

const double TarjetaVacunacion::getX(){
    return propietario->getDomicilio().getLatitud();
}

const double TarjetaVacunacion::getY(){
    return propietario->getDomicilio().getLongitud();
}

