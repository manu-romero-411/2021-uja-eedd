//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#include "Usuario.h"

const string &Usuario::getNombre() const {
    return nombre;
}

void Usuario::setNombre(const string &nombre) {
    Usuario::nombre = nombre;
}

const string &Usuario::getApellidos() const {
    return apellidos;
}

void Usuario::setApellidos(const string &apellidos) {
    Usuario::apellidos = apellidos;
}

const string &Usuario::getNss() const {
    return nss;
}

void Usuario::setNss(const string &nss) {
    this->nss = nss;
}

const Fecha &Usuario::getFechaNacimiento() const {
    return fechaNacimiento;
}

void Usuario::setFechaNacimiento(const Fecha &fechaNacimiento) {
    Usuario::fechaNacimiento = fechaNacimiento;
}

/*const UTM &Usuario::getDomicilio() const {
    return domicilio;
}

void Usuario::setDomicilio(const UTM &dom) {
    Usuario::domicilio = dom;
}*/

Usuario::Usuario(const string &_nombre, const string &_apellidos, const string &_nss, const Fecha &_fechaNacimiento)
        : nombre(_nombre), apellidos(_apellidos), nss(_nss), fechaNacimiento(_fechaNacimiento) {

}

Usuario::Usuario(const string &nombre, const string &apellidos, const string &nss, const int &dia, const int &mes, const int &anno){
    this->nombre = nombre;
    this->apellidos = apellidos;
    this->nss = nss;
    this->fechaNacimiento.anadirDias(dia);
    this->fechaNacimiento.anadirMeses(mes);
    this->fechaNacimiento.anadirAnios(anno);
}

Usuario::Usuario(const Usuario &orig){

}

Usuario::~Usuario() {

}

bool Usuario::operator==(const Usuario &elDeLaDerecha) const {
    return nombre == elDeLaDerecha.nombre &&
           apellidos == elDeLaDerecha.apellidos &&
           nss == elDeLaDerecha.nss &&
           fechaNacimiento.mismoDia(elDeLaDerecha.fechaNacimiento);
}

bool Usuario::operator!=(const Usuario &elDeLaDerecha) const {
    return !(elDeLaDerecha == *this);
}

bool Usuario::operator<(const Usuario &elDeLaDerecha) const {
    /*if (nombre < elDeLaDerecha.nombre)
        return true;
    if (elDeLaDerecha.nombre < nombre)
        return false;
    if (apellidos < elDeLaDerecha.apellidos)
        return true;
    if (elDeLaDerecha.apellidos < apellidos)
        return false;
    if (NSS < elDeLaDerecha.nss)
        return true;
    if (elDeLaDerecha.nss < nss)
        return false;*/
    if ((fechaNacimiento.verAnio() < elDeLaDerecha.fechaNacimiento.verAnio()) && (fechaNacimiento.verMes() < elDeLaDerecha.fechaNacimiento.verMes()) && (fechaNacimiento.verDia() < elDeLaDerecha.fechaNacimiento.verDia()))
        return true;
    else
        return false;

}

bool Usuario::operator>(const Usuario &rhs) const {
    return rhs < *this;
}

bool Usuario::operator<=(const Usuario &rhs) const {
    return !(rhs < *this);
}

bool Usuario::operator>=(const Usuario &rhs) const {
    return !(*this < rhs);
}

ostream &operator<<(ostream &os, const Usuario &usuario) {
    os << "nombre: " << usuario.nombre << " apellidos: " << usuario.apellidos << " NSS: " << usuario.nss
       << " fechaNacimiento: " << usuario.fechaNacimiento;
    return os;
}
