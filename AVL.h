//
// Created by Manuel Jesús Romero Mateos on 22/10/21.

#ifndef EEDD_AVL_H
#define EEDD_AVL_H
#include <stdexcept>

template<class T>
class AVLNodo {
public:
    AVLNodo<T> *ramaIzquierda, *ramaDerecha;
    T dato = nullptr;
    char balance; // -1, 0 , 1 para un árbol AVL

    AVLNodo(T &elemento) : ramaIzquierda(nullptr), ramaDerecha(nullptr), balance(0), dato(elemento) {
    }
    void copiar(AVLNodo<T>* nodoOrig){
        this->dato = nodoOrig->dato;
    }
    //~AVLNodo();
};

template<class T>
class AVL {
private:
    unsigned int numElementos;
    unsigned int altura;
    AVLNodo<T> *nodoRaiz;
    AVLNodo<T>* copiaNodos(AVLNodo<T>* nodoOrig);
    void limpiaArbol(AVLNodo<T> *nodoOrig);
    AVLNodo<T>* buscaClave(T &dato, AVLNodo<T> *p);
    bool operacionInsercion(AVLNodo<T>* &c, T& dato);
    void inorden(AVLNodo<T> *p, int nivel, VDinamico<T*> &datos);
public:
    AVL<T>();
    AVL<T>(const AVL<T> &orig);
    AVL<T>& operator=(const AVL<T> &elDeLaDerecha);
    void rotDer(AVLNodo<T>* &nodo);
    void rotIzq(AVLNodo<T>* &nodo);
    bool inserta(T& dato);
    T* buscaRec(T& dato);
    T* buscaIt(T& dato);
    VDinamico<T*> recorreInorden();
    unsigned int getNumElementos();
    int auxAltura(AVLNodo<T> *nodo, int nivel);
    unsigned int getAltura();
    AVLNodo<T>* getNodoRaiz();
    ~AVL<T>();
};


template<class T>
AVL<T>::AVL(){
    numElementos = 0;
    altura = 0;
    nodoRaiz = nullptr;
}

template<class T>
AVLNodo<T>* AVL<T>::copiaNodos(AVLNodo<T>* nodoOrig){
    if ( nodoOrig != nullptr ){
        AVLNodo<T>* nuevo = new AVLNodo<T>(*nodoOrig);
        numElementos++;
        if (!(this->nodoRaiz)) this->nodoRaiz = nuevo;
        AVLNodo<T>* left = copiaNodos( nodoOrig->ramaIzquierda );
        AVLNodo<T>* right = copiaNodos( nodoOrig->ramaDerecha );
        nuevo->ramaIzquierda = left;
        nuevo->ramaDerecha = right;
        return nuevo;
    } else {
        return nullptr;
    }
}

template<class T>
void AVL<T>::limpiaArbol(AVLNodo<T> *nodoOrig){
    if (nodoOrig) {
        if(nodoOrig->ramaIzquierda) limpiaArbol(nodoOrig->ramaIzquierda);
        if(nodoOrig->ramaDerecha) limpiaArbol(nodoOrig->ramaDerecha);
        delete nodoOrig;
        nodoOrig->ramaIzquierda = nullptr;
        nodoOrig->ramaDerecha = nullptr;
        nodoOrig = nullptr;
        numElementos--;
    }
}


template<class T>
AVL<T>::AVL(const AVL<T> &orig){
    nodoRaiz = new AVLNodo<T>(*orig.nodoRaiz);
    copiaNodos(orig.nodoRaiz);
}

template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T> &elDeLaDerecha){
    limpiaArbol(nodoRaiz);
    copiaNodos(elDeLaDerecha.nodoRaiz);
    return (*this);
}

template<class T>
void AVL<T>::rotDer(AVLNodo<T>* &nodo){
    AVLNodo<T> *q = nodo, *l;
    nodo = l = q->ramaIzquierda;
    q->ramaIzquierda = l->ramaDerecha;
    l->ramaDerecha = q;
    q->balance--;
    if (l->balance > 0) q->balance -= l->balance;
    l->balance--;
    if (q->balance < 0) l->balance -= -q->balance;
}

template<class T>
void AVL<T>::rotIzq(AVLNodo<T>* &nodo){
    AVLNodo<T> *q = nodo, *r;
    nodo = r = q->ramaDerecha;
    q->ramaDerecha = r->ramaIzquierda;
    r->ramaIzquierda = q;
    q->balance++;
    if (r->balance < 0) q->balance += -r->balance;
    r->balance++;
    if (q->balance > 0) r->balance += q->balance;
}

template<class T>
bool AVL<T>::operacionInsercion(AVLNodo<T>* &c, T& dato){
    AVLNodo<T> *p = c;
    bool deltaH = false;
    if (!p) {
        p = new AVLNodo<T>(dato);
        c = p;
        deltaH = true;
        numElementos++;
    } else if (p->dato < dato) {
        if (operacionInsercion(p->ramaDerecha, dato)) {
            p->balance--;
            if (p->balance == -1) deltaH = true;
            else if (p->balance == -2) {
                if (p->ramaDerecha->balance == 1) rotDer(p->ramaDerecha);
                rotIzq(c);
            }
        }
    } else if (dato < p->dato) {
        if (operacionInsercion(p->ramaIzquierda, dato)) {
            p->balance++;
            if (p->balance == 1) deltaH = true;
            else if (p->balance == 2) {
                if (p->ramaIzquierda->balance == -1) rotIzq(p->ramaIzquierda);
                rotDer(c);
            }
        }
    }
    return deltaH;
}

template<class T>
bool AVL<T>::inserta(T &dato) {
    if (numElementos == 0){
        AVLNodo<T>* nuevaRaiz = new AVLNodo<T>(dato);
        nodoRaiz = nuevaRaiz;
        numElementos++;
        return true;
    } else {
        operacionInsercion(nodoRaiz,dato);
    }
}

template <class T>
AVLNodo<T>* AVL<T>::buscaClave(T &dato, AVLNodo<T> *p) {
    if (!p)
        return NULL;
    else if (dato < p->dato)
        return buscaClave(dato, p->ramaIzquierda);
    else if (p->dato < dato)
        return buscaClave(dato, p->ramaDerecha);
    else return p;
}

template<class T>
T* AVL<T>::buscaRec(T& dato){
    AVLNodo<T> *p = buscaClave(dato, nodoRaiz);
    if (p) {
        return &p->dato;
    }
    return NULL;
}

template<class T>
T* AVL<T>::buscaIt(T& dato){
    AVLNodo<T> *p = nodoRaiz;
    if(!p) return NULL;
    while (p) {
        if (dato < p->dato){
            if (p->ramaIzquierda) p = p->ramaIzquierda;
            else return NULL;
        } else {
            if (dato > p->dato){
                if (p->ramaDerecha) p = p->ramaDerecha;
                else return NULL;
            }
        }
        if (dato == p->dato) {
            return &p->dato;
        }
    }
    return nullptr;
}

template<class T>
void AVL<T>::inorden(AVLNodo<T> *p, int nivel, VDinamico<T*> &datos) {
    if (p) {
        inorden(p->ramaIzquierda, nivel + 1, datos);
        datos.insertar(&p->dato,datos.getTamLogico());
        inorden(p->ramaDerecha, nivel + 1, datos);
    }
}

template<class T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> datos;
    inorden(nodoRaiz, 0,datos);
    return datos;
}

template<class T>
unsigned int AVL<T>::getNumElementos(){
    return numElementos;
}

template<class T>
int AVL<T>::auxAltura(AVLNodo<T> *nodo, int nivel) {
    int nuevoNivel = nivel;
    if(nodo != NULL) {
        int nivelIzq = nivel, nivelDer = nivel;
        if (nodo->ramaIzquierda != NULL) {
            nivelIzq = auxAltura(nodo->ramaIzquierda, nivel + 1);
        }

        if (nodo->ramaDerecha != NULL) {
            nivelDer = auxAltura(nodo->ramaDerecha, nivel + 1);
        }

        if (nivelIzq > nivelDer) nuevoNivel = nivelIzq;
        else if (nivelIzq < nivelDer) nuevoNivel = nivelDer;
        else nuevoNivel = nivelIzq;
    }
    return nuevoNivel;
}

template<class T>
unsigned int AVL<T>::getAltura(){
    int altura = auxAltura(nodoRaiz,0);
    return altura;
}

template<class T>
AVLNodo<T>* AVL<T>::getNodoRaiz(){
    return nodoRaiz;
}

template<class T>
AVL<T>::~AVL() {
    limpiaArbol(nodoRaiz);
    numElementos = 0;
}

#endif //EEDD_AVL_H

