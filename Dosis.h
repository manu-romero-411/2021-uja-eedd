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
#include <ostream>
#include "Fecha.h"
//fabricante de la dosis
enum nombreFabricante {
    Pfizer = 0,
    Moderna = 1,
    AstraZeneca = 2,
    Johnson = 3,
};

enum estado {
    administrada = 0,
    enAlmacen = 1,
};

class Dosis {
private:
    int id; //identificador de la dosis concreta
    int idLote; //identificador del lote en la que se contiene
    nombreFabricante fabricante; //Fabricante de la dosis
    Fecha fechaFabricacion;
    Fecha fechaCaducidad;
    estado status;

public:
    Dosis();//Constructor por defecto
    Dosis(const Dosis &orig);//Constructor Copia
    Dosis(int id, int idLote, int idFabricante, int dia, int mes, int anno, int estado);
    Dosis(int _id);
    virtual ~Dosis();//Destructor
    void SetFechaFabricacion(Fecha fechaFabricacion);//Cambia la fecha de fabricación
    Fecha GetFechaFabricacion() const;//Devuelve la fecha de fabricación
    int GetFabricante() const;//Devuelve el fabricante
    void SetIdLote(int idLote);//Cambia el identificador del lote
    int GetIdLote() const;//Devuelve el identificador del lote
    void SetId(int id);//Cambia el identificador de dosis
    int GetId() const;//Cambia el identificador de dosis
    int getStatus() const;
    void setStatus(estado status);
    bool operator<(const Dosis &otra) const;//Compara dosis dependiendo de su identificador
    Dosis& operator=(const Dosis &otro);//Asigna dosis dependiendo de su identificador
    bool operator>(const Dosis &otra) const;//Compara dosis dependiendo de su identificador
    bool operator==(const Dosis &otra) const;//Compara dosis dependiendo de su identificador
    void imprimir();

    friend ostream &operator<<(ostream &os, const Dosis &dosis);
//Muestra por pantalla información básica de la dosis
};
#endif /* DOSIS_H */

