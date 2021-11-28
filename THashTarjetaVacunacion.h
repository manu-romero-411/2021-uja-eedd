//
// Created by Manuel Jesús Romero Mateos on 21/11/21.
//

#ifndef INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
#define INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
#include "TarjetaVacunacion.h"
#include "RandomPrimeGenerator.h"

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
    unsigned long hash2(unsigned long clave, int intento);
    unsigned long hash3(unsigned long clave, int intento);
    int taml, tamf, numColisiones, maximasColisiones;
    vector<CasillaHash> tabla;
public:
    THashTarjetaVacunacion();
    THashTarjetaVacunacion(int tamTabla);
    THashTarjetaVacunacion(const THashTarjetaVacunacion &thash);
    THashTarjetaVacunacion& operator=(const THashTarjetaVacunacion* &thash);
    virtual ~THashTarjetaVacunacion();
    bool insertar(unsigned long clave, TarjetaVacunacion &pal);
    bool buscar(unsigned long clave, TarjetaVacunacion &pal);
    bool borrar(unsigned long clave, string &id);
    unsigned int numTarjetas();
};

unsigned long THashTarjetaVacunacion::hash(unsigned long clave, int intento){
    return (clave + (intento * intento)) % tamf;
}

unsigned long THashTarjetaVacunacion::hash2(unsigned long clave, int intento) {
    int primo = 14341;
    unsigned long h1 = (clave + (intento * intento)) % tamf;
    unsigned long h2 = primo - (clave % primo);
    return (h1 + intento * h2) % tamf;
}

/**
 * @brief Funcion de dispersion doble 2
 */
unsigned long THashTarjetaVacunacion::hash3(unsigned long clave, int intento) {
    int primo = 12611;
    unsigned long h1 = (clave + (intento * intento)) % tamf;
    unsigned long h2 = 1 + (clave % primo);
    return (h1 + intento * h2) % tamf;
}

THashTarjetaVacunacion::THashTarjetaVacunacion(){
    taml = 0;
    tamf = 100000;
    numColisiones = 0;
    tabla = vector<CasillaHash>();
    for (int i=0; i<tamf; i++) {
        TarjetaVacunacion* tarjeta = new TarjetaVacunacion();
        CasillaHash* nueva = new CasillaHash(tarjeta);
        tabla.push_back(*nueva);
    }
}

THashTarjetaVacunacion::THashTarjetaVacunacion(int tamTabla){
    tabla = vector<CasillaHash>();
    taml = 0;
    tamf = tamTabla;
    numColisiones=0;
    maximasColisiones=0;
    for (int i=0; i<tamf; i++) {
        TarjetaVacunacion* tarjeta = new TarjetaVacunacion();
        CasillaHash* nueva = new CasillaHash(tarjeta);
        tabla.push_back(*nueva);
    }
}

THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion &thash){
    tabla = thash.tabla;
    maximasColisiones = thash.maximasColisiones;
    numColisiones = thash.numColisiones;
    taml = thash.taml;
    tamf = thash.tamf;
}

THashTarjetaVacunacion& THashTarjetaVacunacion::operator=(const THashTarjetaVacunacion* &elDeLaDerecha){
    if(this != elDeLaDerecha) {
        tabla = elDeLaDerecha->tabla;
        maximasColisiones = elDeLaDerecha->maximasColisiones;
        numColisiones = elDeLaDerecha->numColisiones;
        taml = elDeLaDerecha->taml;
        tamf = elDeLaDerecha->tamf;
    }
    return *this;
}

THashTarjetaVacunacion::~THashTarjetaVacunacion(){

}

bool THashTarjetaVacunacion::insertar(unsigned long clave, TarjetaVacunacion& pal){
    int intentos = 0, colisiones = 0;
    bool insertado = false;
    TarjetaVacunacion *copiaDato = &pal;
    if ((this->buscar(clave, *copiaDato) == false)){
        do {
            int pos = hash(clave, intentos);
            intentos++;
            if (tabla[pos].estado == CasillaHash::vacia || tabla[pos].estado == CasillaHash::borrada) {
                tabla[pos].dato = &pal;
                tabla[pos].estado = CasillaHash::ocupada;
                insertado = true;
                taml++;
            } else {
                if (tabla[pos].estado == CasillaHash::ocupada) {
                    colisiones++;
                }
            }
        } while (insertado == false);

        if (colisiones > maximasColisiones)
            maximasColisiones = colisiones;
        numColisiones+=colisiones;
        return true;
    } else {
        return false;
    }
}

bool THashTarjetaVacunacion::buscar(unsigned long clave, TarjetaVacunacion &pal){
    bool encontrado = false;
    bool parar = false;
    int intentos = 0;
    do {
        int pos = hash3(clave, intentos);
        ++intentos;
        if (tabla[pos].estado == CasillaHash::borrada || tabla[pos].estado == CasillaHash::vacia) {
            parar = true;

        } else {
            if (tabla[pos].dato->getId() == pal.getId()) {
                //pal = &(tabla[pos].dato);
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
        if(tabla[pos].estado==CasillaHash::vacia){
            if(tabla[pos].estado!=CasillaHash::borrada)
                parar=true;
        } else
        if(tabla[pos].dato->getId()==id){
            tabla[pos].estado = CasillaHash::borrada;
            //tabla[pos].dato = nullptr;
            borrado=true;
            --taml;
        }
    } while (parar == false && borrado == false);
    return borrado;
}

unsigned int THashTarjetaVacunacion::numTarjetas(){
    return taml;
}

#endif //INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
