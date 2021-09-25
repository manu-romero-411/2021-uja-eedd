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
    this->idFabricante = idFabricante;
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

int Dosis::GetFabricante() const{return idFabricante;}

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

template<class T>
bool Dosis<T>::operator==(Dosis &arr) {
    if (tam != arr.tam)
        return false;
    for (int c = 0; c < tam; c++) {
        if (mem[c] != arr.mem[c])
        return false;
    return true;
}

