/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dosis.cpp
 * Author: manuel
 * 
 * Created on 25 de septiembre de 2021, 16:33
 */

#include "Dosis.h"
#include <iostream>
    /* @brief constructor por defecto
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
Dosis::Dosis() {
}

    /* @brief Constructor parametrizado
 * @param[in] -identificador de la dosis y fabricante, fecha
 * @param[out] -
 * @return -
 * 
 * 
 */
Dosis::Dosis(int id, int idLote, int idFabricante, int dia, int mes, int anno, int _estado) {
    this->id = id;
    this->idLote = idLote;
    this->fabricante = nombreFabricante(idFabricante);
    this->fechaFabricacion.asignarDia(dia, mes, anno);
    this->fechaCaducidad = this->fechaFabricacion;
    this->fechaCaducidad.anadirMeses(2);
    this->status = estado(_estado);
}

Dosis::Dosis(int id, int idLote, int idFabricante, int dia, int mes, int anno) {
    this->id = id;
    this->idLote = idLote;
    this->fabricante = nombreFabricante(idFabricante);
    this->fechaFabricacion.asignarDia(dia, mes, anno);
    this->fechaCaducidad = this->fechaFabricacion;
    this->fechaCaducidad.anadirMeses(2);
    this->status = enAlmacen;
}

    /* @brief Constructor copia
 * @param[in] -Referencia a objeto dosis
 * @param[out] -
 * @return -
 * 
 * 
 */
Dosis::Dosis(int _id){
    this->id=_id;
}

Dosis::Dosis(const Dosis &orig):id(orig.id),
                                idLote(orig.idLote),
                                fabricante(orig.fabricante),
                                fechaFabricacion(orig.fechaFabricacion),
                                fechaCaducidad(orig.fechaCaducidad)
{}


    /* @brief Destructor
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
Dosis::~Dosis() {
}

void Dosis::setFechaFabricacion(Fecha fechaFabricacion) {
    this->fechaFabricacion = fechaFabricacion;
}

 
Fecha Dosis::getFechaFabricacion() const {
    return fechaFabricacion;
}

int Dosis::getFabricante() const {return fabricante;}

  
void Dosis::setIdLote(int idLote) {
    this->idLote = idLote;
}

int Dosis::getIdLote() const {
    return idLote;
}

void Dosis::setId(int id) {
    this->id = id;
}

int Dosis::getId() const {
    return id;
}


   /* @brief Operador de igualdad, compara las id
 * @param[in] -Referencia a objeto a comparar
 * @param[out] -
 * @return -
 * 
 * 
 */
bool Dosis::operator==(const Dosis &otra) const {
    return (this->id == otra.id);
}
/* @brief Operador de desigualdad, compara las id
* @param[in] -Referencia a objeto a comparar
* @param[out] -
* @return -
*
*
*/
bool Dosis::operator!=(const Dosis &otra) const {
    return (this->id == otra.id);
}
/* @brief Operador de menor, compara las id
 * @param[in] -Referencia a objeto a comparar
 * @param[out] -
 * @return -
 * 
 * 
 */

bool Dosis::operator<(const Dosis &otra) const{
    return (this->id < otra.id); 
}


/* @brief Operador de mayor, compara las id
 * @param[in] -Referencia a objeto a comparar
 * @param[out] -
 * @return -
 * 
 * 
 */


bool Dosis::operator>(const Dosis &otra) const {
    return (otra.id < this->id); 
}

/* @brief Muestra por pantalla la información de la dosis
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */

Dosis& Dosis::operator=(const Dosis &otro) {
    if(this != &otro) {
        fechaCaducidad = otro.fechaCaducidad;
        fechaFabricacion = otro.fechaFabricacion;
        fabricante = otro.fabricante;
        id = otro.id;
        idLote = otro.idLote;
    }
    return (*this);
}

ostream &operator<<(ostream &os, const Dosis &dosis) {
    os << "ID: " << dosis.id << " | ID Lote: " << dosis.idLote << " | Fabricante: " << dosis.fabricante
       << " | Fecha fabricación: " << dosis.fechaFabricacion.cadenaDia() << " | Fecha caducidad: " << dosis.fechaCaducidad.cadenaDia() << "\n";
    return os;
}

int Dosis::getStatus() const {
    return status;
}

void Dosis::setStatus(estado status) {
    Dosis::status = status;
}
