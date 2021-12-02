/*
 * File:   MallaRegular.h
 * Author: Luis Miguel Valverde Merino, Manuel Jesús Romero Mateos
 *
 * Created on 5 de diciembre de 2019, 13:32
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H
#include <vector>

#include "PuntoRecarga.h"

template<typename T>
class MallaRegular;

template<typename T>
class Casilla {
    list<T> puntos;
public:
    friend class MallaRegular<T>;

    /**
 * @brief Constructor por defecto de la clase Casilla
 */
    Casilla() : puntos() {
    }

    void insertar(const T &dato) {
        puntos.push_back(dato);
    }

    T *buscar(const T &dato){
        typename list<T>::iterator it;
        it = puntos.begin();
        for (; it != puntos.end(); ++it) {
            if (*it == dato)
                return &(*it);
        }
    }
    bool borrar(const T &dato){
        typename list<T>::iterator it;
        it = puntos.begin();
        for (; it != puntos.end(); ++it) {
            if (*it == dato) {
                puntos.erase(it);
                return true;
            }
        }
        return false;
    }
};

template<typename T>
class MallaRegular {
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    vector<vector<Casilla<T> > > mr; // Vector 2D de casillas
    Casilla<T> *obtenerCasilla(float x, float y);
    unsigned int numElementos;
    int nDivX, nDivY;
public:
    MallaRegular();
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
    vector<Casilla<T>>& operator[](int posicion);
    T buscarCercano(float x, float y);
    bool fueraAmbito(float x, float y);
    T buscaEnCasilla(float x, float y);
    T buscaDadaCasilla(float x, float y, Casilla<PuntoRecarga> casilla);
    unsigned maxElementosPorCelda();
    unsigned mediaElementosPorCelda();
    void insertar(float x, float y, const T &dato);
    T *buscar(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);
    int tamEjeX();
    int tamEjeY();
};

template <typename T>
MallaRegular<T>::MallaRegular() : xMin(0), yMin(0), xMax(10), yMax(10), numElementos(0) {
    tamaCasillaX = (xMax - xMin) / 2;
    tamaCasillaY = (yMax - yMin) / 2;
    mr.insert(mr.begin(), 2, vector<Casilla<T> >(2));
}

template <typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY) : xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax) {
    tamaCasillaX = (xMax - xMin) / nDivX;
    tamaCasillaY = (yMax - yMin) / nDivY;
    mr.insert(mr.begin(), nDivY, vector<Casilla<T> >(nDivX));
}

template<typename T>
T MallaRegular<T>::buscarCercano(float x, float y) {
    T cercano;
    double distancia = 1000000;
    Casilla<T> *c;
    for (float i = x - tamaCasillaX; i < x + tamaCasillaX; i += tamaCasillaX) {
        for (float j = y - tamaCasillaY; j < y + tamaCasillaY; j += tamaCasillaY) {
            if (i >= xMin && i <= xMax && j >= yMin && j <= yMax) {
                typename list<T>::iterator it;
                c = obtenerCasilla(i, j);

                for (it = c->puntos.begin(); it != c->puntos.end(); it++) {
                    double d = sqrt(pow((*it).getX() - x, 2) + pow((*it).getY() - y, 2));
                    if (d < distancia) {
                        cercano = *it;
                        distancia = d;
                    }
                }
            }
        }
    }
    return cercano;
}

template<typename T>
bool MallaRegular<T>::fueraAmbito(float x, float y) {
    for (float i = x - tamaCasillaX; i < x + tamaCasillaX; i += tamaCasillaX) {
        for (float j = y - tamaCasillaY; j < y + tamaCasillaY; j += tamaCasillaY) {
            if (i >= xMin && i <= xMax && j >= xMin && j <= xMax) {
                Casilla<T> *c = obtenerCasilla(i, j);
                if (c->puntos.size() != 0) {
                    typename list<T>::iterator it;
                    for (it = c->puntos.begin(); it != c->puntos.end(); it++) {
                        if ((*it).getX() >= x - tamaCasillaX && (*it).getX() <= x + tamaCasillaX && (*it).getY() >= y - tamaCasillaY && (*it).getY() <= y + tamaCasillaY)
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

template <typename T>
unsigned MallaRegular<T>::maxElementosPorCelda() {
    unsigned int maxElementos = 0;
    for (float i = xMin; i <= xMax; i += tamaCasillaX) {
        for (float j = yMin; j <= yMax; j += tamaCasillaY) {
            unsigned tam = obtenerCasilla(i, j)->puntos.size();
            if (tam > maxElementos)
                maxElementos = tam;
        }
    }
    return maxElementos;
}

template <typename T>
unsigned MallaRegular<T>::mediaElementosPorCelda() {
    unsigned numElem = numElementos;
    int numCasillasX = (xMax - xMin) / tamaCasillaX; //Obtengo número de casillas por fila
    int numCasillasY = (yMax - yMin) / tamaCasillaY; //Obtengo número de casillas por columna

    return numElem / (numCasillasX * numCasillasY);
}

template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[j][i];
}

template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    c->insertar(dato);
    numElementos++;
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    if (c->borrar(dato)) {
        numElementos--;
        return true;
    }
    return false;
}

template<typename T>
int MallaRegular<T>::tamEjeX() {
    return this->mr[0].size();
}

template<typename T>
int MallaRegular<T>::tamEjeY() {
    return this->mr.size();
}


#endif /* MALLAREGULAR_H */
