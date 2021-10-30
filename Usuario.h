//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#ifndef EEDD_USUARIO_H
#define EEDD_USUARIO_H

#include <cstdlib>
#include <iostream>
#include "Fecha.h"
#include "Dosis.h"
#include "VDinamico.h"

class Usuario {
private:
    string nombre;
    string apellidos;
    string nss;
    Fecha fechaNacimiento;
    VDinamico<Dosis> misDosis; //Puntero a la dosis asignada al usuario
public:
    VDinamico<Dosis> getMisDosis() const;

    void setMisDosis(VDinamico<Dosis> otrasDosis);
    //UTM domicilio;

    Usuario(const string _nombre, const string _apellidos, const string _nss, const Fecha _fechaNacimiento,
            VDinamico<Dosis> dosis); //Constructor por defecto
    Usuario(const Usuario &orig); //Constructor copia
    const string &getApellidos() const;
    void setApellidos(const string &apellidos);
    const string &getNss() const;
    void setNss(const string &nss);
    const Fecha &getFechaNacimiento() const;
    void setFechaNacimiento(const Fecha &fechaNacimiento);
    std::string getNombre() const;
    void setNombre(const string &nombre);
    //const UTM getDomicilio() const;
    //void setDomicilio(const UTM &dom);

    Usuario& operator=(const Usuario &elDeLaDerecha); //Operador de asignacion
    bool operator==(const Usuario &elDeLaDerecha) const; //Operador de igualdad
    bool operator!=(const Usuario &elDeLaDerecha) const;//Operador de no igualdad
    bool operator<(const Usuario &elDeLaDerecha) const;//Operador de menor (por fecha de nacimiento)
    bool operator>(const Usuario &elDeLaDerecha) const;//Operador de mayor 
    bool operator<=(const Usuario &elDeLaDerecha) const;
    bool operator>=(const Usuario &elDeLaDerecha) const;
    virtual ~Usuario();

    friend ostream &operator<<(ostream &os, const Usuario &usuario); //Operador para imprimir por pantalla
};


#endif //EEDD_USUARIO_H
