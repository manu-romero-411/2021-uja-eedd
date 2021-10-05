/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dosis.h
 * Author: manuel
 *
 * Created on 25 de septiembre de 2021, 16:33
 */

#ifndef DOSIS_H
#define DOSIS_H
#include <cstdlib>
#include "fecha.h"
enum nombreFabricante {
    Pfizer = 0,
    Moderna = 1,
    AstraZeneca = 2,
    Johnson = 3,
};

class Dosis {
private:
    int id;
    int idLote;
    nombreFabricante fabricante;
    Fecha fechaFabricacion;
    Fecha fechaCaducidad;

public:
    Dosis();
    Dosis(const Dosis &orig);
    Dosis(int id, int idLote, int idFabricante, int dia, int mes, int anno);
    virtual ~Dosis();
    void SetFechaFabricacion(Fecha fechaFabricacion);
    Fecha GetFechaFabricacion() const;
    int GetFabricante() const;
    void SetIdLote(int idLote);
    int GetIdLote() const;
    void SetId(int id);
    int GetId() const;
    bool operator<(const Dosis &otra) const;
    bool operator>(Dosis &otra) const;
    bool operator==(Dosis &otra);
    void imprimir();
};
#endif /* DOSIS_H */

