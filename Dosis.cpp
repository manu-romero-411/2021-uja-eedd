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

Dosis::Dosis() {
}

Dosis::Dosis(int id, int idLote, int idFabricante, int dia, int mes, int anno) {
    this->id = id;
    this->idLote = idLote;
    this->fabricante = nombreFabricante(idFabricante);
    this->fechaFabricacion.asignarDia(dia, mes, anno);
    this->fechaCaducidad = this->fechaFabricacion;
    this->fechaCaducidad.anadirMeses(2);
}

Dosis::Dosis(const Dosis& orig) {
}

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

bool Dosis::isEqual(const int b) const{
    return b == id;
}

bool Dosis::operator==(const Dosis &otra) const {
    return otra.isEqual(otra.GetId());
}

bool Dosis::operator<(const Dosis &otra) const{
    if(otra.GetId() > this->id) return true;
    else return false;
}

bool Dosis::operator>(const Dosis &otra) const {
    if(otra.GetId() < this->id) return true;
    else return false;
}

void Dosis::imprimir(){
    std::cout << "Dosis nº "<< id << ": "<<
                                     "\n* ID lote: " << idLote <<
                                     "\n* ID Fabricante: " << fabricante <<
                                     "\n* Fecha de elaboración: " << fechaFabricacion.cadenaDia() << "\n";
}