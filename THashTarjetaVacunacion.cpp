//
// Created by Manuel Jesús Romero Mateos on 2/12/21.
//

#include "THashTarjetaVacunacion.h"

unsigned long THashTarjetaVacunacion::hash(unsigned long clave, int intento){
    return (clave + (intento * intento)) % tamf;
}

unsigned long THashTarjetaVacunacion::djb2(unsigned char* claveStr){
    unsigned long hash = 5381;
    int c;
    while (c = *claveStr++){
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

THashTarjetaVacunacion::THashTarjetaVacunacion(){
    tabla = vector<CasillaHash>();
    taml = 0;
    tamf = 0;
    numColisiones=0;
    maximasColisiones=0;
    numMax10=0;
}

THashTarjetaVacunacion::THashTarjetaVacunacion(int tamTabla){
    tabla = vector<CasillaHash>();
    taml = 0;
    tamf = tamTabla;
    numColisiones=0;
    maximasColisiones=0;
    numMax10=0;
    CasillaHash rellenar;
    for (int i=0; i<tamf; i++) {
        tabla.push_back(rellenar);
    }
}

THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion &thash){
    tabla = thash.tabla;
    maximasColisiones = thash.maximasColisiones;
    numColisiones = thash.numColisiones;
    numMax10= thash.numMax10;
    taml = thash.taml;
    tamf = thash.tamf;
}

THashTarjetaVacunacion& THashTarjetaVacunacion::operator=(const THashTarjetaVacunacion &elDeLaDerecha){
    tabla = elDeLaDerecha.tabla;
    maximasColisiones = elDeLaDerecha.maximasColisiones;
    numColisiones = elDeLaDerecha.numColisiones;
    taml = elDeLaDerecha.taml;
    tamf = elDeLaDerecha.tamf;
    return *this;
}

THashTarjetaVacunacion::~THashTarjetaVacunacion(){

}

bool THashTarjetaVacunacion::insertar(unsigned long clave, TarjetaVacunacion &pal){
    int intentos = 0, colisiones = 0;
    bool insertado = false;
    TarjetaVacunacion *copiaDato = &pal;
    string newid= pal.getId();
    if (!(this->buscar(clave, newid, *copiaDato)))
    {
        do {
            int pos = hash(clave, intentos);
            intentos++;
            if (tabla[pos].estado == 0) {
                tabla[pos].dato = &pal;
                tabla[pos].estado = CasillaHash::ocupada;
                insertado = true;
                taml++;
            } else {
                if (tabla[pos].estado == CasillaHash::ocupada) {
                    colisiones++;
                }
            }
        } while (!insertado);

        if (colisiones > 10){
            numMax10++;

        }
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
        int pos = hash(clave, intentos);
        ++intentos;
        if (tabla[pos].estado == 0) {
            parar = true;

        } else {
            if (tabla[pos].dato->getId() == id) {
                pal = *tabla[pos].dato; //TODO CREO QUE ESTO ESTA MAL MIRALO JOSAN DEL FUTURO
                encontrado = true;
            }
        }

    } while (!encontrado && !parar);

    return encontrado;
}

bool THashTarjetaVacunacion::borrar(unsigned long clave, string &id){
    bool borrado=false;
    bool parar=false;
    int intentos=0;
    do {
        int pos=hash(clave, intentos);
        ++intentos;
        if(tabla[pos].estado==CasillaHash::vacia){
            if(tabla[pos].estado!=CasillaHash::borrada)
                parar=true;
        }else
        if(tabla[pos].dato->getId()==id){
            tabla[pos].estado=CasillaHash::borrada;
            borrado=true;
            --taml;
        }
    } while(!parar && !borrado);

    return borrado;
}

unsigned int THashTarjetaVacunacion::numTarjetas(){
    return taml;
}

int THashTarjetaVacunacion::NumMax10() const {
    return numMax10;
}

int THashTarjetaVacunacion::MaximasColisiones() const {
    return maximasColisiones;
}

float THashTarjetaVacunacion::promedioColisiones() const  {
    return taml/numColisiones;

}

float THashTarjetaVacunacion::factorCarga() {
    cout<< tamf <<std::endl;
    return taml/tamf;
}

int THashTarjetaVacunacion::tamTabla() const {
    return tamf;
}

