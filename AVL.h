//
// Created by Manuel Jesús Romero Mateos on 22/10/21.

#ifndef EEDD_AVL_H
#define EEDD_AVL_H
#include <stdexcept>

template<class T>
class AVLNodo {
public:
    AVLNodo<T> *ramaIzquierda, *ramaDerecha; //Puntero a los hijos por la derecha e izquierda
    T dato = nullptr; //Dato contenido
    char balance; // -1, 0 , 1 para un árbol AVL

    AVLNodo(T &elemento) : ramaIzquierda(nullptr), ramaDerecha(nullptr), balance(0), dato(elemento) {
    } //Constructor parametrizado
    void copiar(AVLNodo<T>* nodoOrig){
        this->dato = nodoOrig->dato;
    } //Constructor copia
    //~AVLNodo();
};

template<class T>
class AVL {
private:
    unsigned int numElementos; //elementos totales en el arbol
    unsigned int altura; //Profundidad del arbol
    AVLNodo<T> *nodoRaiz; //Puntero al primer nodo
    AVLNodo<T>* copiaNodos(AVLNodo<T>* nodoOrig); //Funcion para copiar subarboles dandole un nodo
    void limpiaArbol(AVLNodo<T> *nodoOrig); //Funcion para eliminar arboles dandole un nodo
    AVLNodo<T>* buscaClave(T &dato, AVLNodo<T> *p); //Busca un dato concreto y devuelve el nodo en el que está
    bool operacionInsercion(AVLNodo<T>* &c, T& dato); //Inserta un nodo en el árbol ordenadamente
    void inorden(AVLNodo<T> *p, int nivel, VDinamico<T*> &datos); //Recorre el arbol en inorden y pasa los datos a un Vdinamico
public:
    AVL<T>(); //Constructor por defecto
    AVL<T>(const AVL<T> &orig);//Constructor copia
    AVL<T>& operator=(const AVL<T> &elDeLaDerecha); //Operador de asignación
    void rotDer(AVLNodo<T>* &nodo); //Función para hacer rotaciones a la derecha
    void rotIzq(AVLNodo<T>* &nodo);//Funcion para hacer rotaciones a la izquierda
    bool inserta(T& dato); //Inserta un dato
    T* buscaRec(T& dato);  //Busqueda recursiva de un dato
    T* buscaIt(T& dato); //Busqueda iterativa de un dato
    VDinamico<T*> recorreInorden(); //Recorre en inorden el árbol, y mete los elementos en un Vdinamico
    unsigned int getNumElementos(); //Devuelve el numero de elementos totales del arbol
    int auxAltura(AVLNodo<T> *nodo, int nivel); //Funcion auxiliar para calcular la altura del arbol
    unsigned int getAltura(); //Devuelve la altura del arbol
    AVLNodo<T>* getNodoRaiz(); //Devuelve un puntero al primer elemento
    ~AVL<T>();
};
/**
* @brief Constructor por defecto
* @param[in]
* @param[out] -
* @return -
*
*
*/

template<class T>
AVL<T>::AVL(){
    numElementos = 0;
    altura = 0;
    nodoRaiz = nullptr;
}
/**
* @brief   Copia los nodos en inorden de un subarbol a partir de un nodo (funciona de forma recursiva)
* @param[in] Nodo sobre el que empezar
* @param[out] -
* @return Nodo creado
*
*
*/
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
/**
* @brief Va eliminando los datos del arbol y deshaciendo las relaciones
* @param[in] Un nodo en el que empezar
* @param[out] -
* @return -
*
*
*/
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

/**
* @brief Constructor copia, necesita copiaNodos
* @param[in] Árbol AVL que copiar
* @param[out] -
* @return -
*
*
*/
template<class T>
AVL<T>::AVL(const AVL<T> &orig){
    nodoRaiz = new AVLNodo<T>(*orig.nodoRaiz);
    copiaNodos(orig.nodoRaiz);
}
/**
* @brief Operador de asignacion (Necesita copiaNodos)
* @param[in] AVL que copiar
* @param[out] -
* @return -
*
*
*/
template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T> &elDeLaDerecha){
    limpiaArbol(nodoRaiz);
    copiaNodos(elDeLaDerecha.nodoRaiz);
    return (*this);
}

/**
* @brief Rota los nodos hacia la derecha
* @param[in] Nodo desbalanceado en el que empezar la rotación
* @param[out] -
* @return -
*
*
*/
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
/**
* @brief Rota los nodos hacia la izquierda
* @param[in] Nodo desbalanceado en el que empezar la rotación
* @param[out] -
* @return -
*
*
*/
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
/**
* @brief Inserción del árbol
* @param[in] Nodo en el que insertar y dato a insertar
* @param[out]-
* @return  Booleano si se ha podido insertar el dato
*
*
*/
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
/**
* @brief Inserta un dato en el arbol (Necesita operacionInsercion)
* @param[in] Dato a insertar
* @param[out] -
* @return Booleano si se ha podido insertar el dato
*
*
*/
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

/**
* @brief Busca un dato en un subarbol
* @param[in]
* @param[out] -
* @return Puntero al Nodo en el que está el dato
*
*
*/
template <class T>
AVLNodo<T>* AVL<T>::buscaClave(T &dato, AVLNodo<T> *p) {
    if (!p)
        return 0;
    else if (dato < p->dato)
        return buscaClave(dato, p->ramaIzquierda);
    else if (p->dato < dato)
        return buscaClave(dato, p->ramaDerecha);
    else return p;
}

/**
* @brief Busca Recursiva (Necesita BuscaClave)
* @param[in]
* @param[out] -
* @return Dato encontrado
*
*
*/
template<class T>
T* AVL<T>::buscaRec(T& dato){
    AVLNodo<T> *p = buscaClave(dato, nodoRaiz);
    if (p) {
        return &p->dato;
    }
    return NULL;
}
/**
* @brief Búsqueda interativa de un dato, empezando dese del nodo raiz
* @param[in] Dato a buscar
* @param[out] -
* @return Puntero al dato encontrado
*
*
*/
template<class T>
T* AVL<T>::buscaIt(T& dato){
    AVLNodo<T> *p = nodoRaiz;
    if(!p) return 0;
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

/**
* @brief De forma recursiva, inserta los elementos del árbol en un vector
* @param[in] Nodo en el que empezar, nivel actual, vector en el que insertar los datos
* @param[out] -
* @return -
*
*
*/
template<class T>
void AVL<T>::inorden(AVLNodo<T> *p, int nivel, VDinamico<T*> &datos) {
    if (p) {
        inorden(p->ramaIzquierda, nivel + 1, datos);
        datos.insertar(&p->dato,datos.getTamLogico());
        inorden(p->ramaDerecha, nivel + 1, datos);
    }
}
/**
* @brief Crea un vector con los datos del arbol insertados inorden (necesita inorden)
* @param[in]
* @param[out]
* @return Vdinamico con los datos
*
*
*/
template<class T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> datos;
    inorden(nodoRaiz, 0,datos);
    return datos;
}
/**
* @brief Retorna el numero de elementos totales
* @param[in]
* @param[out]
* @return Entero con los elementos totales
*
*
*/
template<class T>
unsigned int AVL<T>::getNumElementos(){
    return numElementos;
}
/**
* @brief Funcion que calcula y compara la altura los subarboles (De forma recursiva)
* @param[in] Nodo en el que empezar, nivel actual
* @param[out]
* @return Nivel actualizado
*
*
*/
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
/**
* @brief Devuelve la altura del arbol (Necesita auxAltura)
* @param[in]
* @param[out] -
* @return entero indicando la altura del arbol
*
*
*/
template<class T>
unsigned int AVL<T>::getAltura(){
    int altura = auxAltura(nodoRaiz,0);
    return altura;
}
/**
* @brief Devuelve el primer nodo
* @param[in]
* @param[out] -
* @return Puntero al primer nodo
*
*
*/
template<class T>
AVLNodo<T>* AVL<T>::getNodoRaiz(){
    return nodoRaiz;
}
/**
* @brief Destructor (Necesita limpiaArbol)
* @param[in]
* @param[out]
* @return 
*
*
*/
template<class T>
AVL<T>::~AVL() {
    limpiaArbol(nodoRaiz);
    numElementos = 0;
}

#endif //EEDD_AVL_H

