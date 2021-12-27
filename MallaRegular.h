/*
 * File:   MallaRegular.h
 *
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H
#include <vector>
#include <climits>

template<typename T>
class MallaRegular;

template<typename T>
class Casilla {
    std::list<T> puntos;
    friend class MallaRegular<T>;
public:
    Casilla();
    void insertar(const T& dato);
    T* buscar(const T& dato);
    bool borrar(const T &dato);
};

template<typename T>
Casilla<T>::Casilla():puntos(){}

template<typename T>
bool Casilla<T>::borrar(const T& dato){
    typename std::list<T>::iterator it;
    for(it = puntos.begin();it != puntos.end();++it){
        if(*it == dato) {
            puntos.erase(it);
            return true;
        }
    }
    return false;
}
template<typename T>
T* Casilla<T>::buscar(const T& dato){
    typename std::list<T>::iterator it;
    for(it=puntos.begin();it!=puntos.end();++it){
        if(*it == dato){
            return &(*it);
        }
    }
    return 0;
}
template<typename T>
void Casilla<T>::insertar(const T& dato){
    puntos.push_back(dato);
}

template<class T>
class MallaRegular{
    float xMin{}, yMin{}, xMax{}, yMax{};
    float tamCasillaX,tamCasillaY;
    int numElem{};
    std::vector<std::vector<Casilla<T>>> malla;
    Casilla<T>* getCasilla(float X, float Y);
    float teoremaPitagoras(float a, float b);
    float teoremaPitagorasInverso(float c, float b);
    int divX,divY;
public:
    MallaRegular(float _xMin, float _yMin, float _xMax, float _yMax, int nDivX, int nDivY);
    MallaRegular<T>& operator=(const MallaRegular<T>& orig);
    void insertar(float x, float y, const T& dato);
    T* buscar(float x, float y, const T& dato);
    bool borrar(float x, float y, const T& dato);
    T* buscarCercano(double x, double y);
    vector<T> buscarRadio(double xCentro, double yCentro, double radio);
    bool fueraAmbito(double x, double y);
    unsigned int maxElementosPorCelda();
    unsigned int mediaElementosPorCelda();
    int getNumElem();
    int getNumCeldas();
    vector<T> getAll();
};


template<class T>
MallaRegular<T>::MallaRegular(float _xMin, float _yMin, float _xMax, float _yMax, int nDivX, int nDivY){
    this->xMin = _xMin - 0.01;
    this->yMin = _yMin - 0.01;
    this->xMax = _xMax + 0.01;
    this->yMax = _yMax + 0.01; // HAY QUE HACER ESTO DE SUMAR/RESTAR 0.01, PARA QUE NO HAYA BAD ACCESS AL INSERTAR LOS PUNTOS EXTREMOS
    this->numElem = 0;
    this->divX = nDivX;
    this->divY = nDivY;
    tamCasillaX = ((xMax - xMin) / nDivX);
    tamCasillaY = ((yMax - yMin) / nDivY);
    malla.insert(malla.begin(), nDivX, std::vector<Casilla<T>>(nDivY));
}

template <class T>
MallaRegular<T>& MallaRegular<T>::operator=(const MallaRegular<T>& orig){
    this->xMin = orig.xMin;
    this->yMin = orig.yMin;
    this->xMax = orig.xMax;
    this->yMax = orig.yMax;
    this->numElem = orig.numElem;
    tamCasillaX = orig.tamCasillaX;
    tamCasillaY = orig.tamCasillaX;
    malla = orig.malla;
    return *this;
}

template<class T>
Casilla<T>* MallaRegular<T>::getCasilla(float X, float Y){
    int i = (X-xMin)/tamCasillaX;
    int j = (Y-yMin)/tamCasillaY;
    return &malla[i][j];
}

template<class T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato){
    Casilla<T>* c = getCasilla(x, y);
    bool resultado;
    resultado = c->borrar(dato);
    if(resultado){
        numElem--;
    }
    return resultado;
}

template<class T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    Casilla<T>* c = getCasilla(x, y);
    c->insertar(dato);
    numElem++;
}

template<class T>
T* MallaRegular<T>::buscar(float x, float y, const T& dato){
    Casilla<T> *c = getCasilla(x, y);
    return c->buscar(dato);
}

template<class T>
T* MallaRegular<T>::buscarCercano(double x, double y){
    int i = (x - xMin) / tamCasillaX;
    int j = (y - yMin) / tamCasillaY;
    int auxi = i,auxj = j;
    bool encontrado = false;
    int distancia = UINT_MAX;
    T* cercano = nullptr;

    while(!encontrado){
        for (int f = (i - 1); f <= (auxi + 1); ++f){
            for (int c = (j - 1); c <= (auxj + 1); ++c){
                if(i > 0 && j > 0){
                    if(malla[f][c].puntos.size() > 0){
                        encontrado = true;
                        for (auto it = malla[f][c].puntos.begin(); it != malla[f][c].puntos.end(); ++it){
                            float dist = teoremaPitagoras(it->getX() - x, it->getY() - y);
                            if (dist < distancia){
                                distancia = dist;
                                cercano = new T(*it);
                            }
                        }
                    }
                }
            }
        }
        i = i - 1;
        j = j - 1;
        auxi = auxi + 1;
        auxj = auxj + 1;
    }
    return cercano;
}

template<class T>
vector<T> MallaRegular<T>::buscarRadio(double xCentro, double yCentro, double radio){
    vector<T> result;
    int iMinima = (xCentro - radio - xMin) / tamCasillaX;
    int jMinima = (yCentro - radio - yMin) / tamCasillaY;
    int iMaxima = (xCentro + radio - xMin) / tamCasillaX;
    int jMaxima = (yCentro + radio - yMin) / tamCasillaY;
    //int cuantosHaVisto = 0;

    if(iMinima < 0) iMinima = 0;
    if(jMinima < 0) jMinima = 0;
    if(iMaxima > divX - 1) iMaxima = divX;
    if(jMaxima > divY - 1) jMaxima = divY;

    for (int f = iMinima; f < iMaxima; ++f){
        for (int c = jMinima; c < jMaxima; ++c){
            if(malla[f][c].puntos.size() > 0){
                list<T>* ll = &malla[f][c].puntos;
                //cuantosHaVisto += ll->size();
                for (typename std::list<T>::iterator it = ll->begin(); it != ll->end(); ++it){
                    double xDist = abs(xCentro - (*it)->getX());
                    double yDist = abs(yCentro - (*it)->getY());
                    double distanciaF = teoremaPitagoras(xDist, yDist);
                    if (distanciaF <= radio){
                        result.push_back(*it);
                    }
                }
            }
        }
    }
    return result;
}

template <class T>
float MallaRegular<T>::teoremaPitagoras(float a, float b){
    float aCuad = (pow(a,2));
    float bCuad = (pow(b,2));
    return sqrt(aCuad + bCuad);
}

template <class T>
float MallaRegular<T>::teoremaPitagorasInverso(float b, float c){
    float cCuad = (pow(c,2));
    float bCuad = (pow(b,2));
    return sqrt(cCuad - bCuad);
}

template<class T>
bool MallaRegular<T>::fueraAmbito(double x, double y){
    int i = (x - xMin) / tamCasillaX;
    int j = (y - yMin) / tamCasillaY;
    int auxI, auxJ;
    bool fuera = true;

    if(malla[i][j].puntos.size() > 0){
        fuera = false;
    } else {
        i = i - 1;
        j = j - 1;
        auxI = auxI + 1;
        auxJ = auxJ + 1;

        for(int f = i; f <= auxI; f++){
            for(int c = j; c <= auxJ; c++){
                if(i > 0 && j > 0){
                    if(malla[f][c].puntos.size() > 0){
                        fuera = false;
                    }
                }
            }
        }
    }

    return fuera;
}

template<class T>
unsigned int MallaRegular<T>::maxElementosPorCelda(){
    int max = 0;
    for(int i = 0; i < malla.size(); ++i){
        for(int j = 0; j < malla.size(); ++j){
            if(malla[i][j].puntos.size() > max){
                max = malla[i][j].puntos.size();
            }
        }
    }
    return max;
}

template<class T>
unsigned int MallaRegular<T>::mediaElementosPorCelda(){
    return (numElem / this->getNumCeldas());
}

template<class T>
int MallaRegular<T>::getNumElem(){
    return numElem;
}

template<class T>
vector<T> MallaRegular<T>::getAll(){
    vector<T> result;
    for (int i = 0; i < malla.size(); ++i){
        for (int j = 0; j < malla[i].size(); ++j){
            list<T>* cc = &malla[i][j].puntos;
            for(typename std::list<T>::iterator it = cc->begin(); it != cc->end(); ++it){
                result.push_back(*it);
            }
        }
    }
    return result;
}

template<class T>
int MallaRegular<T>::getNumCeldas(){
    int resultado = 0;
    for(int i = 0; i < malla.size(); i++){
        resultado += malla[i].size();
    }
    return resultado;
}
#endif /* MALLAREGULAR_H */
