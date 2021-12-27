//
// Created by Manuel Jesús Romero Mateos on 21/11/21.
//

#ifndef INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
#define INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
#include "TarjetaVacunacion.h"

class CasillaHash{
    friend class THashTarjetaVacunacion;
private:
    enum EstadoCasillaHash{
        vacia = 0,
        ocupada = 1,
        borrada = -1,

    };
    EstadoCasillaHash estado;
    TarjetaVacunacion* dato;
public:
    CasillaHash(){
        this->dato= nullptr;
        estado=vacia;

    }
    explicit CasillaHash(TarjetaVacunacion* newdato){
       this->dato = newdato ;
       this->estado= vacia;
    }
};

class THashTarjetaVacunacion {
private:
    unsigned long hash(unsigned long clave, int intento);
    int taml, tamf, numColisiones, maximasColisiones, numMax10;
    vector<CasillaHash> tabla;

public:
    THashTarjetaVacunacion();
    int tamTabla() const;
    int MaximasColisiones() const;
    int NumMax10() const;
    THashTarjetaVacunacion(int tamTabla);
    THashTarjetaVacunacion(const THashTarjetaVacunacion &thash);
    THashTarjetaVacunacion& operator=(const THashTarjetaVacunacion &thash);
    virtual ~THashTarjetaVacunacion();
    bool insertar(unsigned long clave, TarjetaVacunacion &pal);
    bool buscar(unsigned long clave, string &id, TarjetaVacunacion &pal);
    bool borrar(unsigned long clave, string &id);
    unsigned int numTarjetas();
    float promedioColisiones() const;
    float factorCarga();
    unsigned long djb2(unsigned char* claveStr);
};

#endif //INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
