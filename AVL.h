//
// Created by Manuel Jesús Romero Mateos on 22/10/21.
//

#ifndef EEDD_AVL_H
#define EEDD_AVL_H

template<class T>
class AVLNodo {
public:
    AVLNodo<T> *ramaIzquierda, *ramaDerecha;
    T dato = nullptr;
    char balance; // -1, 0 , 1 para un árbol avl

    AVLNodo(T &elemento) : ramaIzquierda(nullptr), ramaDerecha(nullptr), balance(0), dato(elemento) {
    }
};

template<class T>
class AVL {
private:
    unsigned int numElementos;
    unsigned int altura;
    AVLNodo<T> *nodoRaiz;
    void copiaNodos(const AVLNodo<T>* &nodoOrig, const AVLNodo<T>* &nodoDestino);
    void limpiaArbol(const AVLNodo<T>* &nodoOrig);

public:
    AVL<T>();
    AVL<T>(const AVL<T> &orig);
    AVL<T>& operator=(const AVL<T> &elDeLaDerecha);
    void rotDer(Nodo<T>* &nodo);
    void rotIzq(Nodo<T>* &nodo);
    bool inserta(T& dato);
    bool buscaNR(T& dato, T& result);
    bool buscaIt(T& dato, T& result);
    void recorreInorden();
    unsigned int getNumElementos();
    unsigned int getAltura();
    ~AVL<T>();
};


template<class T>
AVL<T>::AVL(){
    numElementos = 0;
    altura = 0;
    nodoRaiz = nullptr;
}

template<class T>
void AVL<T>::copiaNodos(const AVLNodo<T>* &nodoOrig, const AVLNodo<T>* &nodoDestino){
    if (nodoOrig) {
        nodoDestino = new AVLNodo<T>(*nodoOrig);
        copiaNodos(nodoOrig->ramaIzquierda,nodoDestino->ramaIzquierda);
        copiaNodos(nodoOrig->ramaDerecha,nodoDestino->ramaDerecha);
    } else
        nodoDestino = nullptr;
}

template<class T>
void AVL<T>::limpiaArbol(const AVLNodo<T>* &nodoOrig){
    if (nodoOrig) {
        limpiaArbol(nodoOrig->ramaIzquierda);
        limpiaArbol(nodoOrig->ramaDerecha);
        delete nodoOrig;
        nodoOrig = nullptr;
    }
}

template<class T>
AVL<T>::AVL(const AVL<T> &orig){
    copiaNodos(orig.nodoRaiz, nodoRaiz);
}

template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T> &elDeLaDerecha){
    limpiaArbol(nodoRaiz);
    copiarNodos(elDeLaDerecha.nodoRaiz, this->nodoRaiz);
}

template<class T>
void AVL<T>::rotDer(Nodo<T>* &nodo){

}

template<class T>
void AVL<T>::rotIzq(Nodo<T>* &nodo){

}

template<class T>
bool AVL<T>::inserta(T& dato){

}

template<class T>
bool AVL<T>::buscaNR(T& dato, T& result){

}

template<class T>
bool AVL<T>::buscaIt(T& dato, T& result){

}

template<class T>
void AVL<T>::recorreInorden(){

}

template<class T>
unsigned int AVL<T>::getNumElementos(){
    return numElementos;
}

template<class T>
unsigned int AVL<T>::getAltura(){
    return altura;
}

template<class T>
AVL<T>::~AVL(){

}

#endif //EEDD_AVL_H
