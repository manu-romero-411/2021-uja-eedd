//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#ifndef EEDD_USUARIO_H
#define EEDD_USUARIO_H

#include <cstdlib>
#include <iostream>
#include "Fecha.h"

using namespace std;

class Usuario {
private:
    string nombre;
    string apellidos;
    string nss;
    Fecha fechaNacimiento;
    //UTM domicilio;
public:
    Usuario(const string &nombre, const string &apellidos, const string &nss, const Fecha &fechaNacimiento);
    Usuario(const string &nombre, const string &apellidos, const string &nss, const int &dia, const int &mes, const int &anno);
    Usuario(const Usuario &orig);
    const string &getApellidos() const;
    void setApellidos(const string &apellidos);
    const string &getNss() const;
    void setNss(const string &nss);
    const Fecha &getFechaNacimiento() const;
    void setFechaNacimiento(const Fecha &fechaNacimiento);
    const string &getNombre() const;
    void setNombre(const string &nombre);
    //const UTM getDomicilio() const;
    //void setDomicilio(const UTM &dom);

    bool operator==(const Usuario &elDeLaDerecha) const;
    bool operator!=(const Usuario &elDeLaDerecha) const;
    bool operator<(const Usuario &elDeLaDerecha) const;
    bool operator>(const Usuario &elDeLaDerecha) const;
    bool operator<=(const Usuario &elDeLaDerecha) const;
    bool operator>=(const Usuario &elDeLaDerecha) const;
    virtual ~Usuario();

    friend ostream &operator<<(ostream &os, const Usuario &usuario);
};


#endif //EEDD_USUARIO_H
