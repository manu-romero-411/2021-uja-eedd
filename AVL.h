//
// Created by Manuel Jesús Romero Mateos on 22/10/21.
//

/*
 *
 * #ifndef EEDD_AVL_H
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
    AVLNodo<T>* buscaClave(T &dato, AVLNodo<T> *p);
    bool buscaRec(T& dato, T& result);
    bool buscaIt(T& dato, T& result);
    VDinamico<T*> inorden(AVLNodo<T> *p, int nivel);
    VDinamico<T*> recorreInorden();
    unsigned int getNumElementos();
    int auxAltura(AVLNodo<T> *nodo, int nivel);
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
    AVLNodo<T> *q = nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0) l->bal -= -q->bal;

}

template<class T>
void AVL<T>::rotIzq(Nodo<T>* &nodo){
    AVLNodo<T> *q = nodo, *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0) r->bal += q->bal;
}

//template<class T>
bool AVL<T>::inserta(T& dato){
    AVLNodo<T> *p = c;
    int deltaH = false;
    if (!p) {
        p = new AVLNodo<T>(dato);
        c = p;
        deltaH = true;
        _numElementos++;
    } else if (p->dato < dato) {
        if (inserta(p->der, dato)) {
            p->bal--;
            if (p->bal == -1) deltaH = true;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der);
                rotIzq(c);
            }
        }
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1) deltaH = true;
            else if (p->bal == 2) {
                if (p->izq->bal == -1) rotIzq(p->izq);
                rotDer(c);
            }
        }
    }
    return deltaH;
}

template <class T>
AVLNodo<T>* AVL<T>::buscaClave(T &dato, AVLNodo<T> *p) {
    if (!p)
        return 0;
    else if (dato < p->dato)
        return buscaClave(dato, p->izq);
    else if (p->dato < dato)
        return buscaClave(dato, p->der);
    else return p;
}

template<class T>
bool AVL<T>::buscaRec(T& dato, T& result){
    AVLNodo<T> *p = buscaClave(dato, nodoRaiz);
    if (p) {
        result = p->dato;
        return true;
    }
    return false;
}

template<class T>
bool AVL<T>::buscaIt(T& dato, T& result){
    AVLNodo<T> *p = buscaClave(dato, nodoRaiz);
    while (!vacio(p)) {
        if (dato == p->dato) {
            result = p->dato;
            return true;
        } else if (dato < p->dato) p = p->izq;
        else if (p->dato < dato) p = p->der;
    }
    return false;
}

template<class T>
VDinamico<T*> AVL<T>::inorden(AVLNodo<T> *p, int nivel) {
    VDinamico<T*> datos;
    if (p) {
        VDinamico<T*> datosIzq = inorden(p->izq, nivel + 1);
        T& datoRaiz = p->dato;
        VDinamico<T*> datosDer = inorden(p->der, nivel + 1);
        for (int i = 0; i < datosIzq.getTamLogico();++i){
            datos.insertar(datos.getTamLogico(),datosIzq[i]);

        datos.insertar(datos.getTamLogico(),datoRaiz);
        for (int i = 0; i < datosDer.getTamLogico();++i){
            datos.insertar(datos.getTamLogico(),datosDer[i]);
        }
    }
    return datos;
}

template<class T>
VDinamico<T*> AVL<T>::recorreInorden() {
    return inorden(nodoRaiz, 0);
}

template<class T>
unsigned int AVL<T>::getNumElementos(){
    return numElementos;
}

template<class T>
int AVL<T>::auxAltura(AVLNodo<T> *nodo, int nivel) {
    int larosaliaIzq = 0;
    int larosaliaDer = 0;
    if (nodo->izq)
        larosaliaIzq = auxAltura(nodo->izq, nivel + 1);
    if (nodo->der)
        larosaliaDer = auxAltura(nodo->der, nivel + 1);
    if ((nodo->der == NULL)&&(nodo->izq == NULL))
        return 0;
    if (larosaliaDer >= larosaliaIzq)
        return larosaliaDer;
    else
        return larosaliaIzq;
}

template<class T>
unsigned int AVL<T>::getAltura(){
    return auxAltura(nodoRaiz,0);
}

template<class T>
AVL<T>::~AVL() {
    limpiaArbol(nodoRaiz);
    delete nodoRaiz;
}

#endif //EEDD_AVL_H
    */
