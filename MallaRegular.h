/*
 * File:   MallaRegular.h
 * Author: Luis Miguel Valverde Merino, Manuel Jesús Romero Mateos
 *
 * Created on 5 de diciembre de 2019, 13:32
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H
#include <vector>

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
    float tamCasillaX, tamCasillaY; // Tamaño real de cada casilla
    vector<vector<Casilla<T> > > mr; // Vector 2D de casillas
    Casilla<T> *obtenerCasilla(float x, float y);
    unsigned int numElementos;
    int nDivX, nDivY;
public:
    MallaRegular();
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int _nDivX, int _nDivY);
    MallaRegular<T>& operator=(const MallaRegular<T>& orig);
    vector<Casilla<T>>& operator[](int posicion);
    T buscarCercano(float x, float y);
    bool fueraRango(float x, float y);
    T buscaEnCasilla(float x, float y);
    T buscaDadaCasilla(float x, float y, Casilla<T> casilla);
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
    tamCasillaX = (xMax - xMin) / 2;
    tamCasillaY = (yMax - yMin) / 2;
    mr.insert(mr.begin(), 2, vector<Casilla<T> >(2));
}

template <typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int _nDivX, int _nDivY){
    this->xMin = aXMin;
    this->yMin = aYMin;
    this->xMax = aXMax;
    this->yMax = aYMax;
    this->nDivY = _nDivY;
    this->nDivX = _nDivX;
    this->numElementos = 0;
    tamCasillaX = (xMax - xMin) / nDivX;
    tamCasillaY = (yMax - yMin) / nDivY;
    mr.insert(mr.begin(), nDivY, vector<Casilla<T> >(nDivX));
}

template<typename T>
T MallaRegular<T>::buscarCercano(float x, float y) {
    T cercano;
    double distancia = 1000000;
    Casilla<T> *c;
    for (float i = x - tamCasillaX; i < x + tamCasillaX; i += tamCasillaX) {
        for (float j = y - tamCasillaY; j < y + tamCasillaY; j += tamCasillaY) {
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
bool MallaRegular<T>::fueraRango(float x, float y) {
    for (float i = x - tamCasillaX; i < x + tamCasillaX; i += tamCasillaX) {
        for (float j = y - tamCasillaY; j < y + tamCasillaY; j += tamCasillaY) {
            if (i >= xMin && i <= xMax && j >= xMin && j <= xMax) {
                Casilla<T> *c = obtenerCasilla(i, j);
                if (c->puntos.size() != 0) {
                    typename list<T>::iterator it;
                    for (it = c->puntos.begin(); it != c->puntos.end(); it++) {
                        if ((*it).getX() >= x - tamCasillaX && (*it).getX() <= x + tamCasillaX && (*it).getY() >= y - tamCasillaY && (*it).getY() <= y + tamCasillaY)
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

template <typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() {
    unsigned int maxElementos = 0;
    for (float i = xMin; i <= xMax; i += tamCasillaX) {
        for (float j = yMin; j <= yMax; j += tamCasillaY) {
            unsigned tam = obtenerCasilla(i, j)->puntos.size();
            if (tam > maxElementos)
                maxElementos = tam;
        }
    }
    return maxElementos;
}

template <typename T>
unsigned int MallaRegular<T>::mediaElementosPorCelda() {
    unsigned numElem = numElementos;
    int numCasillasX = (xMax - xMin) / tamCasillaX; //Obtengo número de casillas por fila
    int numCasillasY = (yMax - yMin) / tamCasillaY; //Obtengo número de casillas por columna

    return numElem / (numCasillasX * numCasillasY);
}

template<typename T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamCasillaX;
    int j = (y - yMin) / tamCasillaY;
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

template<typename T>
MallaRegular<T>& MallaRegular<T>::operator=(const MallaRegular<T>& orig){
    xMin = orig.xMin;
    yMin = orig.yMin;
    xMax = orig.xMax;
    yMax = orig.yMax;
    tamCasillaX = orig.tamCasillaX;
    tamCasillaY = orig.tamCasillaY;
    mr = orig.mr;
    numElementos = orig.numElementos;
    nDivX = orig.nDivX;
    nDivY = orig.nDivY;
    return *this;
}


#endif /* MALLAREGULAR_H */
