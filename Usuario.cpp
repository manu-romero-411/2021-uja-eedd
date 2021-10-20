//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#include "Usuario.h"

Usuario::Usuario(const string _nombre, const string _apellidos, const string _nss, const Fecha _fechaNacimiento,
                 Dosis &_miDosis)
        : nombre(_nombre), apellidos(_apellidos), nss(_nss), fechaNacimiento(_fechaNacimiento), miDosis(&_miDosis) {
}

Usuario::Usuario(const Usuario &orig){
    this->nombre = orig.nombre;
    this->apellidos = orig.apellidos;
    this->nss = orig.nss;
    this->fechaNacimiento.asignarDia(orig.fechaNacimiento.verDia(),orig.fechaNacimiento.verMes(),orig.fechaNacimiento.verAnio());
    this->miDosis = orig.miDosis;
}

Usuario& Usuario::operator=(const Usuario &elDeLaDerecha){
    if(this != &elDeLaDerecha) {
        nombre = elDeLaDerecha.nombre;
        apellidos = elDeLaDerecha.apellidos;
        nss = elDeLaDerecha.nss;
        fechaNacimiento = elDeLaDerecha.fechaNacimiento;
        miDosis = elDeLaDerecha.miDosis;
    }
    return (*this);
}

std::string Usuario::getNombre() const {
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

Dosis &Usuario::getMiDosis() const {
    return *miDosis;
}

void Usuario::setMiDosis(Dosis &miDosis) {
    this->miDosis = &miDosis;
}

bool Usuario::operator==(const Usuario &elDeLaDerecha) const {
    return nombre == elDeLaDerecha.nombre &&
           apellidos == elDeLaDerecha.apellidos &&
           nss == elDeLaDerecha.nss &&
           fechaNacimiento.mismoDia(elDeLaDerecha.fechaNacimiento) &&
           miDosis == elDeLaDerecha.miDosis;
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
    os << "Nombre: " << usuario.nombre << " | Apellidos: " << usuario.apellidos << " | NSS: " << usuario.nss
       << " | Fecha de Nacimiento: " << usuario.fechaNacimiento.cadenaDia() << " | Dosis: " << usuario.miDosis->GetId();
    return os;
}

Usuario::~Usuario() {

}
