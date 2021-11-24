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


    explicit CasillaHash(TarjetaVacunacion* newdato){
       this->dato = newdato ;
       this->estado= vacia;
    }
};



class THashTarjetaVacunacion {
private:
    unsigned long hash(unsigned long clave, int intento);
    int taml, tamf, numColisiones, maximasColisiones;
    vector<CasillaHash> tabla;
public:
    THashTarjetaVacunacion(int tamTabla);
    THashTarjetaVacunacion(const THashTarjetaVacunacion &thash);
    THashTarjetaVacunacion& operator=(const THashTarjetaVacunacion &thash);
    ~THashTarjetaVacunacion();
    bool insertar(unsigned long clave, TarjetaVacunacion &pal);
    bool buscar(unsigned long clave, string &id, TarjetaVacunacion &pal);
    bool borrar(unsigned long clave, string &id);
    unsigned int numTarjetas();
};

unsigned long THashTarjetaVacunacion::hash(unsigned long clave, int intento){
    return (clave + (intento * intento)) % tamf;
}

THashTarjetaVacunacion::THashTarjetaVacunacion(int tamTabla){
    tabla = vector<CasillaHash>();
    taml = 0;
    tamf = tamTabla;
    numColisiones=0;
    maximasColisiones=0;
    for (int i=0; i<tamf; i++) {
        tabla.push_back(Entrada());//TODO
    }
}

THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion &thash){
    tabla = thash.tabla;
    maximasColisiones = thash.maximasColisiones;
    numColisiones = thash.numColisiones;
    taml = thash.taml;
    tamf = thash.tamf;
}

THashTarjetaVacunacion& THashTarjetaVacunacion::operator=(const THashTarjetaVacunacion &elDeLaDerecha){
    tabla = elDeLaDerecha.tabla;
    maximasColisiones = elDeLaDerecha.maximasColisiones;
    numColisiones = elDeLaDerecha.numColisiones;
    taml = elDeLaDerecha.taml;
    tamf = elDeLaDerecha.tamf;
}

~THashTarjetaVacunacion(){

}

bool THashTarjetaVacunacion::insertar(unsigned long clave, TarjetaVacunacion &pal){
    int intentos = 0, colisiones = 0;
    bool insertado = false;
    TarjetaVacunacion *copiaDato = &pal;
    if ((this->buscar(clave, dni, copiaDato)) == false)//TODO
         {
        do {
            int pos = hash(clave, intentos);
            intentos++;
            if (tabla[pos].estado == 0) {
                tabla[pos].dato = *pal;
                tabla[pos].estado = ocupada;
                insertado = true;
                taml++;
                tabla[pos].
            } else {
                if (tabla[pos].estado == ocupada) {
                    colisiones++;
                }
            }
        } while (insertado == false);

        if (colisiones > maximasColisiones)
            maximasColisiones = colisiones;

        numColisiones+=colisiones;

        return true;
    } else
        return false;
}

bool THashTarjetaVacunacion::buscar(unsigned long clave, string &id, TarjetaVacunacion &pal){
    bool encontrado = false;
    bool parar = false;
    int intentos = 0;
    do {
        int pos = hash3(clave, intentos);
        ++intentos;
        if (tabla[pos].estado == 0) {
            parar = true;

        } else {
            if (tabla[pos].dato.GetDni() == dni) {
                cli = &(tabla[pos].dato);
                encontrado = true;
            }
        }

    } while (encontrado == false && parar == false);

    return encontrado;
}

bool THashTarjetaVacunacion::borrar(unsigned long clave, string &id){
    bool borrado=false;
    bool parar=false;
    int intentos=0;
    do {
        int pos=hash3(clave, intentos);
        ++intentos;
        if(tabla[pos].estado==vacia){
            if(tabla[pos].estado!=disponible)
                parar=true;
        }else
        if(tabla[pos].dato.GetDni()==dni){
            tabla[pos].estado=disponible;
            borrado=true;
            --taml;
        }
    } while(parar == false && borrado == false);

    return borrado;
}

unsigned int THashTarjetaVacunacion::numTarjetas(){
    return taml;
}

#endif //INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
