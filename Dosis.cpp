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

bool Dosis::operator==(Dosis &otra) {
    //if(otra.GetFabricante() != this->idFabricante) return false;
    //if(otra.GetFechaFabricacion() != this->fechaFabricacion ) return false;
    if(otra.GetId() != this->id) return false;
    //if(otra.GetIdLote() != this->idLote) return false;
    return true;
}

bool Dosis::operator<(const Dosis &otra) const{
    if(otra.GetId() > this->id) return true;
    else return false;
}

bool Dosis::operator>(Dosis &otra) const {
    if(otra.GetId() < this->id) return true;
    else return false;
}