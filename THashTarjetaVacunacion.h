//
// Created by Manuel Jesús Romero Mateos on 21/11/21.
//

#ifndef INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H
#define INC_2021_EEDD_PRACTICAS_THASHTARJETAVACUNACION_H


class THashTarjetaVacunacion {
private:
    unsigned long hash(unsigned long clave, int intento);
    int taml, tamf, numColisiones, maximasColisiones;
    vector<> tabla;
public:
    THashTarjetaVacunacion(int tamTabla);
    THashTarjetaVacunacion(THashTarjetaVacunacion &thash);
    operator=(THashTarjetaVacunacion &thash);
    ~THashTarjetaVacunacion();
    bool insertar(unsigned long clave, TarjetaVacunacion &pal);
    bool buscar(unsigned long clave, string &id, TarjetaVacunacion &*pal);
    bool borrar(unsigned long clave, string &id);
    unsigned int numTarjetas();
};

unsigned long hash(unsigned long clave, int intento){
    return (clave + (intento * intento)) % tamf;
}

THashTarjetaVacunacion::THashTarjetaVacunacion(int tamTabla){
    tabla = vector<Entrada>();
    taml = 0;
    tamf = tamTabla;
    numColisiones=0;
    maximasColisiones=0;
    for (int i=0; i<tamf; i++) {
        tabla.push_back(Entrada());
    }
}

THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion &thash){
    tabla = thash.tabla;
    maximasColisiones = thash.maximasColisiones;
    numColisiones = thash.numColisiones;
    taml = thash.taml;
    tamf = thash.tamf;
}

THashTarjetaVacunacion::operator=(const THashTarjetaVacunacion &elDeLaDerecha){
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
    Cliente *copiaDato = &cli;
    if ((this->buscar(clave, dni, copiaDato)) == false) {
        do {
            int pos = hash(clave, intentos);
            intentos++;
            if (tabla[pos].estado == vacia) {
                tabla[pos].dato = cli;
                tabla[pos].estado = ocupada;
                insertado = true;
                taml++;
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

bool THashTarjetaVacunacion::buscar(unsigned long clave, string &id, TarjetaVacunacion &*pal){
    bool encontrado = false;
    bool parar = false;
    int intentos = 0;
    do {
        int pos = hash3(clave, intentos);
        ++intentos;
        if (tabla[pos].estado == vacia) {
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
