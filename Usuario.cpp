//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#include "Usuario.h"
/**
 * @brief Constructor parametrizado
 * @param[in] -string de conmbre, apellidos, nss. Fecha de nacimiento tipo fecha
 * @param[out] -
 * @return -
 *
 *
 */
Usuario::Usuario(){

}

Usuario::Usuario(const string _nombre, const string _apellidos, const string _nss, const Fecha _fechaNacimiento) {
    this->nombre = _nombre;
    this->apellidos = _apellidos;
    this->nss = _nss;
    this->fechaNacimiento = _fechaNacimiento;
    int anyoActual = 2021;
    int mesActual = 10;
    int diaActual = 19;
    int edad = anyoActual - this->fechaNacimiento.verAnio();
    if (this->fechaNacimiento.verMes() > mesActual) {
        edad--;
    } else {
        if ((fechaNacimiento.verDia() > diaActual) && ((this->fechaNacimiento.verMes() == mesActual))) {
            edad--;
        }
    }
    this->edad = edad;

}

/**
 * @brief Constructor copia
 * @param[in] - Referencia a un objeto tipo Usuario
 * @param[out] -
 * @return -
 *
 *
 */
Usuario::Usuario(const Usuario &orig){
    this->nombre = orig.nombre;
    this->apellidos = orig.apellidos;
    this->nss = orig.nss;
    this->fechaNacimiento.asignarDia(orig.fechaNacimiento.verDia(),orig.fechaNacimiento.verMes(),orig.fechaNacimiento.verAnio());
    this->edad=orig.edad;
    this->misDosis = orig.misDosis;
}
/**
 * @brief Operador de asignación
 * @param[in] -  Referencia a un objeto de tipo usuario
 * @param[out] -
 * @return -
 *
 *
 */

Usuario& Usuario::operator=(const Usuario* &elDeLaDerecha){

    if(this != elDeLaDerecha) {
        nombre = elDeLaDerecha->nombre;
        apellidos = elDeLaDerecha->apellidos;
        nss = elDeLaDerecha->nss;
        fechaNacimiento = elDeLaDerecha->fechaNacimiento;
        misDosis = elDeLaDerecha->misDosis;
        edad=elDeLaDerecha->edad;
        this->misDosis = elDeLaDerecha->misDosis;

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

const UTM Usuario::getDomicilio()  {
    return domicilio;
}

void Usuario::setDomicilio(const UTM &dom) {
    Usuario::domicilio = dom;
}

Dosis& Usuario::getDosis(int cual){

    if(cual < misDosis.size()) {
      return *misDosis[cual];
    }
    else
        throw std::out_of_range("[Usuario] Posición no valida al llamar a VDinamico<Dosis>");
}

void Usuario::nuevaDosis(Dosis* nueva){
    Dosis* p= nueva;
    misDosis.push_back(p);
    p->setStatus(administrada);
}

/**
 * @brief Operador de igualdad
 * @param[in] -Referencia a objeto de tipo Usuario
 * @param[out] -
 * @return True si los objetos son iguales en nombre, apellidos, nss, y fecha de nacimiento
 *
 *
 */

bool Usuario::operator==(const Usuario &elDeLaDerecha) const {
    return nombre == elDeLaDerecha.nombre &&
           apellidos == elDeLaDerecha.apellidos &&
           nss == elDeLaDerecha.nss &&
           fechaNacimiento.mismoDia(elDeLaDerecha.fechaNacimiento) &&
           this->misDosis == elDeLaDerecha.misDosis;
}

/**
 * @brief Operador de no igualdad
 * @param[in] - Referencia a objeto de tipo Usuario
 * @param[out] -
 * @return True si no son iguales
 *
 *
 */
bool Usuario::operator!=(const Usuario &elDeLaDerecha) const {
    return !(elDeLaDerecha == *this);
}

/**
 * @brief Ordena a los usuarios por su fecha de nacimiento
 * @param[in] - Referencia a objeto de tipo Usuario
 * @param[out] -
 * @return -True si la fecha del primero es menor que la del segundo, false en caso contrario
 *
 *
 */
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
    if (this->nss < elDeLaDerecha.nss)
        return true;
    else
        return false;

}

bool Usuario::operator>(const Usuario &rhs) const {
    if(this->nss > rhs.nss)
        return true;
    else return false;
}

bool Usuario::operator<=(const Usuario &rhs) const {
    return !(rhs < *this);
}

bool Usuario::operator>=(const Usuario &rhs) const {
    return !(*this < rhs);
}

/**
 * @brief Operador de impresión
 * @param[in] - Referecnia a la clase de salida por pantalla, una referencia a un objeto de tipo usuario
 * @param[out] -
 * @return -
 *
 *
 */
ostream &operator<<(ostream &os, const Usuario &usuario) {
    os << "Nombre: " << usuario.nombre << " | Apellidos: " << usuario.apellidos << " | NSS: " << usuario.nss
       << " | Fecha de Nacimiento: " << usuario.fechaNacimiento.cadenaDia();
    return os;
}
/**
 * @brief Destructor por defecto
 * @param[in] -
 * @param[out] -
 * @return -
 *
 *
 */


int Usuario::getedad() {
   /* int anyoActual = 2021;
    int mesActual = 10;
    int diaActual = 19;
    int edad = anyoActual- this->fechaNacimiento.verAnio();
    if  (this->fechaNacimiento.verMes() > mesActual) {
        edad--;
    } else {
        if ((fechaNacimiento.verDia() > diaActual) && ((this->fechaNacimiento.verMes() == mesActual))){
            edad--;
        }
    }*/
    return edad;
}

vector<Dosis*> Usuario::getmisdosis(){
    return misDosis;
}

nombreFabricante Usuario::getdosisRecomendable(){
    if ( edad >= 12 && edad < 30)
        return Johnson;
    if (edad >= 30 && edad < 50)
        return AstraZeneca;
    if (edad >= 50 && edad < 65)
        return Moderna;
    if (edad >= 65)
        return Pfizer;
    if (edad < 12)
        return ninguno;
}

bool Usuario::isDosisRec(){
    return dosisRecomendada;
}

void Usuario::tieneDosisRec(bool rec){
    dosisRecomendada = rec;
}

Usuario::~Usuario() {

}

int Usuario::dosisPorAdministrar(){
    if (edad >= 75) return 3 - misDosis.size();
    if (edad < 12) return 0;
    if (edad >= 12 && edad < 75) return 2 - misDosis.size();
}
