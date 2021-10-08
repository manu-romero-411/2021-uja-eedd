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
Dosis::Dosis(int id, int idLote, int idFabricante, int dia, int mes, int anno) {
    this->id = id;
    this->idLote = idLote;
    this->fabricante = nombreFabricante(idFabricante);
    this->fechaFabricacion.asignarDia(dia, mes, anno);
    this->fechaCaducidad = this->fechaFabricacion;
    this->fechaCaducidad.anadirMeses(2);
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

void Dosis::SetFechaFabricacion(Fecha fechaFabricacion) {
    this->fechaFabricacion = fechaFabricacion;
}

 
Fecha Dosis::GetFechaFabricacion() const {
    return fechaFabricacion;
}

int Dosis::GetFabricante() const {return fabricante;}

  
void Dosis::SetIdLote(int idLote) {
    this->idLote = idLote;
}

int Dosis::GetIdLote() const {
    return idLote;
}

void Dosis::SetId(int id) {
    this->id = id;
}

int Dosis::GetId() const {
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

void Dosis::imprimir(){
    std::cout << "Dosis nº "<< id << ": "<<
                                     "\n* ID lote: " << idLote <<
                                     "\n* ID Fabricante: " << fabricante <<
                                     "\n* Fecha de elaboración: " << fechaFabricacion.cadenaDia() << "\n";
}